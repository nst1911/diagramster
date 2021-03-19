#include "basicobjectserializer.h"
#include "basicobjectmetafactory.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMetaProperty>
#include <QDebug>

QByteArray diagramster::BasicObjectXMLSerializer::serialize(BasicObject *object, diagramster::BasicObjectXMLSerializer::Result *result)
{
    QByteArray byteArray;
    QXmlStreamWriter writer(&byteArray);
    writer.setAutoFormatting(true);

    auto writeResult = writeBasicObjectRecursively(object, &writer);

    (*result) = writeResult;
    return (writeResult == Success) ? byteArray : QByteArray();
}

diagramster::BasicObject *diagramster::BasicObjectXMLSerializer::deserialize(const QByteArray &bytes, diagramster::BasicObjectSerializer::Result *result)
{
    QXmlStreamReader reader(bytes);
    BasicObjectSerializer::Result readResult;

    QList<ParsedPropertyData> propertyData;

    auto object = readBasicObjectRecursively(&reader, &readResult, &propertyData);

    for (auto data : propertyData)
    {
        if (data.result != Success) {
            readResult = data.result;
            break;
        }

        // If setProperty() returns false, a new dynamic property will be added
        // We don't need to add NEW dynamic properties to a BasicObject, we restore old ones
        if (!(data.object)->setProperty((data.propertyName).toUtf8().constData(), (data.propertyValue)))
        {
            qWarning() << "BasicObjectXMLSerializer::readProperty() : Property" << (data.propertyName) <<
                          "of " << (data.object)->objectName() << "parsing error (was added as a dynamic one)";

            readResult = ObjectError;
            break;
        }
    }

    (*result) = readResult;
    return (readResult == Success) ? object : nullptr;
}

diagramster::BasicObjectSerializer::Result diagramster::BasicObjectXMLSerializer::writeBasicObjectRecursively(BasicObject *object, QXmlStreamWriter *writer)
{
    if (!object) return ObjectError;

    auto metaObject = object->metaObject();
    if (!metaObject) return ObjectError;

    writer->writeStartElement(BASIC_OBJECT_ELEMENT_NAME);
    writer->writeAttribute(TYPE_ATTRIBUTE_NAME, metaObject->className());
    writer->writeAttribute(OBJECT_NAME_ATTRIBUTE_NAME, object->objectName());
    writer->writeAttribute(UID_ATTRIBUTE_NAME,  object->uid().toString());

    int count = metaObject->propertyCount();

    for (int i = 0; i < count; ++i)
    {
        auto property = metaObject->property(i);
        auto propertyName = property.name();
        auto propertyValue = object->property(propertyName);

        // canConvert<QString> must be before canConvert<QStringList> because
        // QVariant containing QString can be converted to QStringList and it will be
        // processed as a list property later

        if (!strcmp(propertyName, BasicObject::OBJECT_NAME_PROPERTY_NAME) || !strcmp(propertyName, BasicObject::UID_PROPERTY_NAME))
            continue;

        if (propertyValue.canConvert<QString>())
        {
            writer->writeTextElement(propertyName, propertyValue.toString());
        }
        else if (propertyValue.canConvert<QStringList>())
        {
            auto list = propertyValue.toStringList();
            if (list.isEmpty()) continue;

            writer->writeStartElement(propertyName);

            for (auto listElem : list)
                writer->writeTextElement(PROPERTY_LIST_ELEMENT_NAME, listElem);

            writer->writeEndElement();
        }
        else {
            qWarning() << "BasicObjectXMLSerializer::writeBasicObjectRecursively() : Can't convert property" << propertyName << "to QString or QStringList";
            return ParsingError;
        }

    }

    auto children = object->basicObjectChildren();

    if (!children.empty())
    {
        for (auto child : children)
        {
            auto result = writeBasicObjectRecursively(child, writer);
            if (result != Success) {
                qWarning() << "BasicObjectXMLSerializer::writeBasicObjectRecursively() : (result != Success) while iterating children; result =" << result;
                return result;
            }
        }
    }

    writer->writeEndElement();

    return writer->hasError() ? ParsingError : Success;
}

diagramster::BasicObject *diagramster::BasicObjectXMLSerializer::readBasicObjectRecursively(QXmlStreamReader *reader,
                                                                                            Result* result,
                                                                                            QList<ParsedPropertyData>* propertyData,
                                                                                            ReadFromXmlBehaviour behaviour)
{
    // TODO: Split the method to submethods like processPropertyElement(), processBasicObjectElement() etc
    // TODO: Clean the method, it looks kinda clumsy

    BasicObject* basicObject = nullptr;

    if (behaviour == Default)
        reader->readNextStartElement();

    while (!reader->atEnd() && !reader->hasError())
    {
        if (reader->isStartElement())
        {
            // Found a basic object
            if (reader->name() == BASIC_OBJECT_ELEMENT_NAME)
            { 
                if (!basicObject) // If the basic object is root
                {
                    auto attributes = reader->attributes();

                    auto type = attributes.value(TYPE_ATTRIBUTE_NAME).toString();
                    auto name = attributes.value(OBJECT_NAME_ATTRIBUTE_NAME).toString();
                    auto uid  = attributes.value(UID_ATTRIBUTE_NAME).toString();

                    if (name.isNull()) qWarning() << "BasicObjectXMLSerializer::readBasicObjectRecursively() : BasicObject name parsing error";
                    if (name.isNull()) qWarning() << "BasicObjectXMLSerializer::readBasicObjectRecursively() : BasicObject name parsing error";
                    if (uid.isNull())  qWarning() << "BasicObjectXMLSerializer::readBasicObjectRecursively() : BasicObject UID parsing error";

                    basicObject = BasicObjectMetaFactory::create(type, name, Q_NULLPTR, uid);

                    if (!basicObject) {
                        qWarning() << "BasicObjectXMLSerializer::readBasicObjectRecursively() : BasicObject creating error (!basicObject)";
                        (*result) = Result::ParsingError;
                        return nullptr;
                    }
                }
                else  // If the basic object is a root's child
                {
                    Result readResult;
                    auto child = readBasicObjectRecursively(reader, &readResult, propertyData, ReadChild);

                    if (child && readResult == Success)
                    {
                        child->setParent(basicObject);
                        reader->readNextStartElement();
                        continue;
                    }
                    else
                    {
                        qWarning() << "BasicObjectXMLSerializer::readBasicObjectRecursively() : Child of " << basicObject->objectName() << "parsing error";
                        (*result) = readResult;
                        return nullptr;
                    }
                }
            }

            // Found something that can be a property
            else
            {
                if (!basicObject) continue; // The basic object has to be found to this moment

                auto data = readProperty(reader, basicObject);

                if (data.result != Success)
                    return nullptr;
                else
                    propertyData->append(data);
            }
        }

        if (reader->isEndElement() && reader->name() == BASIC_OBJECT_ELEMENT_NAME)
            break;

        reader->readNextStartElement();
    }

    (*result) = basicObject ? Success : ParsingError;
    return basicObject;
}

diagramster::BasicObjectXMLSerializer::ParsedPropertyData diagramster::BasicObjectXMLSerializer::readProperty(QXmlStreamReader *reader, BasicObject *basicObject)
{
    ParsedPropertyData data;

    data.object = basicObject;
    data.propertyName  = reader->name().toString();
    data.propertyValue = basicObject->property(data.propertyName.toUtf8().constData());

    if (!data.propertyValue.isValid()) {
        qWarning() << "BasicObjectXMLSerializer::readProperty() : Invalid property name" << data.propertyName << "of " << data.object->objectName();
        data.result = ParsingError;
        return data;
    }

    // canConvert<QString> must be before canConvert<QStringList> because
    // QVariant containing QString can be converted to QStringList and it will be
    // processed as a list property later

    if (data.propertyValue.canConvert<QString>()) // If property can be converted to QString
    {
        data.propertyValue = reader->readElementText();
    }
    else if (data.propertyValue.canConvert<QStringList>()) // If property is a list of something
    {
        QStringList list;

        reader->readNextStartElement();

        while (!reader->atEnd() && !reader->hasError())
        {
            if (reader->isEndElement() && reader->name() == data.propertyName)
                break;

            if (reader->name() == PROPERTY_LIST_ELEMENT_NAME)
            {
                auto elementText = reader->readElementText();
                if (elementText.isEmpty())
                    qWarning() << "BasicObjectXMLSerializer::readProperty() : List property element data is empty (property"
                               << data.propertyName << "of" <<  data.object->objectName()  << ")";

                list.append(elementText);
            }

            reader->readNextStartElement();
        }

        data.propertyValue = list;
    }
    else
    {
        qWarning() << "BasicObjectXMLSerializer::readProperty() : Property" << data.propertyName << "of " << data.object->objectName() << "can't be converted to QString or QStringList";
        data.result = ObjectError;
        return data;
    }

    if (reader->hasError()) {
        qWarning() << "BasicObjectXMLSerializer::readProperty() :(reader->hasError()) (property"
                   << data.propertyName << "of" <<  data.object->objectName()  << ")";
        data.result = ParsingError;
        return data;
    }


    data.result = Success;

    return data;
}
