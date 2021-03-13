#include "figureserializer.h"
#include "figurefactory.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMetaProperty>
#include <QDebug>

QByteArray diagramster::FigureXMLSerializer::serialize(diagramster::Figure *figure, diagramster::FigureXMLSerializer::Result *result)
{
    QByteArray byteArray;
    QXmlStreamWriter writer(&byteArray);
    writer.setAutoFormatting(true);

    auto writeResult = writeFigureRecursively(figure, &writer);

    (*result) = writeResult;
    return (writeResult == Success) ? byteArray : QByteArray();
}

diagramster::Figure *diagramster::FigureXMLSerializer::deserialize(const QByteArray &bytes, diagramster::FigureSerializer::Result *result)
{
    QXmlStreamReader reader(bytes);
    FigureSerializer::Result readResult;

    auto figure = readFigureRecursively(&reader, &readResult);

    (*result) = readResult;
    return (readResult == Success) ? figure : nullptr;
}

diagramster::FigureSerializer::Result diagramster::FigureXMLSerializer::writeFigureRecursively(diagramster::Figure *figure, QXmlStreamWriter *writer)
{
    if (!figure) return ObjectError;

    auto metaObject = figure->metaObject();
    if (!metaObject) return ObjectError;

    writer->writeStartElement(FIGURE_ELEMENT_NAME);
    writer->writeAttribute(FIGURE_TYPE_ATTRIBUTE_NAME, metaObject->className());
    writer->writeAttribute(FIGURE_NAME_ATTRIBUTE_NAME, figure->objectName());
    writer->writeAttribute(FIGURE_UID_ATTRIBUTE_NAME,  figure->uid().toString());

    int count = metaObject->propertyCount();

    for (int i = 0; i < count; ++i)
    {
        auto property = metaObject->property(i);
        auto propertyName = property.name();
        auto propertyValue = figure->property(propertyName);

        // canConvert<QString> must be before canConvert<QStringList> because
        // QVariant containing QString can be converted to QStringList and it will be
        // processed as a list property later

        if (!strcmp(propertyName, Figure::OBJECT_NAME_PROPERTY_NAME) || !strcmp(propertyName, Figure::UID_PROPERTY_NAME))
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
            qWarning() << "FigureXMLSerializer::writeFigureRecursively() : Can't convert property" << propertyName << "to QString or QStringList";
            return ParsingError;
        }

    }

    auto children = figure->figureChildren();

    if (!children.empty())
    {
        for (auto child : children)
        {
            auto result = writeFigureRecursively(child, writer);
            if (result != Success) {
                qWarning() << "FigureXMLSerializer::writeFigureRecursively() : (result != Success) while iterating children; result =" << result;
                return result;
            }
        }
    }

    writer->writeEndElement();

    return writer->hasError() ? ParsingError : Success;
}

diagramster::Figure *diagramster::FigureXMLSerializer::readFigureRecursively(QXmlStreamReader *reader, diagramster::FigureSerializer::Result *result, diagramster::FigureXMLSerializer::ReadFromXmlBehaviour behaviour)
{
    // TODO: Split the method to submethods like processPropertyElement(), processFigureElement() etc
    // TODO: Clean the method, it looks kinda clumsy

    Figure* figure = nullptr;

    if (behaviour == Default)
        reader->readNextStartElement();

    while (!reader->atEnd() && !reader->hasError())
    {
        if (reader->isStartElement())
        {
            // Found a figure
            if (reader->name() == FIGURE_ELEMENT_NAME)
            { 
                if (!figure) // If the figure is a root figure
                {
                    auto attributes = reader->attributes();

                    auto type = attributes.value(FIGURE_TYPE_ATTRIBUTE_NAME).toString();
                    auto name = attributes.value(FIGURE_NAME_ATTRIBUTE_NAME).toString();
                    auto uid  = attributes.value(FIGURE_UID_ATTRIBUTE_NAME).toString();

                    if (name.isNull()) qWarning() << "FigureXMLSerializer::readFigureRecursively() : Figure name parsing error";
                    if (name.isNull()) qWarning() << "FigureXMLSerializer::readFigureRecursively() : Figure name parsing error";
                    if (uid.isNull())  qWarning() << "FigureXMLSerializer::readFigureRecursively() : Figure UID parsing error";

                    figure = FigureFactory::create(type, name, uid, Q_NULLPTR);

                    if (!figure) {
                        qWarning() << "FigureXMLSerializer::readFigureRecursively() : Figure creating error (!figure)";
                        (*result) = Result::ParsingError;
                        return nullptr;
                    }
                }
                else  // If the figure is a root's child
                {
                    Result readResult;
                    auto child = readFigureRecursively(reader, &readResult, ReadChild);

                    if (child && readResult == Success)
                    {
                        child->setParent(figure);
                        reader->readNextStartElement();
                        continue;
                    }
                    else
                    {
                        qWarning() << "FigureXMLSerializer::readFigureRecursively() : Child of " << figure->objectName() << "parsing error";
                        (*result) = readResult;
                        return nullptr;
                    }
                }
            }

            // Found something that can be a property
            else
            {
                if (!figure) continue; // The figure has to be found to this moment

                if (readProperty(reader, figure) != Success)
                    return nullptr;
            }
        }

        if (reader->isEndElement() && reader->name() == FIGURE_ELEMENT_NAME)
            break;

        reader->readNextStartElement();
    }

    (*result) = figure ? Success : ParsingError;
    return figure;
}

diagramster::FigureSerializer::Result diagramster::FigureXMLSerializer::readProperty(QXmlStreamReader *reader, diagramster::Figure *figure)
{
    QString propertyName = reader->name().toString();

    auto propertyValue = figure->property(propertyName.toUtf8().constData());

    if (!propertyValue.isValid()) {
        qWarning() << "FigureXMLSerializer::readFigureRecursively() : Invalid property name" << propertyName;
        return ParsingError;
    }

    // canConvert<QString> must be before canConvert<QStringList> because
    // QVariant containing QString can be converted to QStringList and it will be
    // processed as a list property later

    if (propertyValue.canConvert<QString>()) // If property can be converted to QString
    {
        propertyValue = reader->readElementText();
    }

    else if (propertyValue.canConvert<QStringList>()) // If property is a list of something
    {
        QStringList list;

        reader->readNextStartElement();

        while (!reader->atEnd() && !reader->hasError())
        {
            if (reader->isEndElement() && reader->name() == propertyName)
                break;

            if (reader->name() == PROPERTY_LIST_ELEMENT_NAME)
            {
                auto elementText = reader->readElementText();
                if (elementText.isEmpty())
                    qWarning() << "FigureXMLSerializer::readFigureRecursively() : List property element data is empty (property"
                               << propertyName << "of" << figure->objectName()  << ")";

                list.append(elementText);
            }

            reader->readNextStartElement();
        }

        propertyValue = list;
    }

    else
    {
        qWarning() << "FigureXMLSerializer::readFigureRecursively() : Property" << propertyName << "of " << figure->objectName() << "can't be converted to QString or QStringList";
        return ObjectError;
    }

    if (!reader->hasError())
    {
        if (!figure->setProperty(propertyName.toUtf8().constData(), propertyValue)) {
            // If setProperty() returns false, a new dynamic property will be added
            // We don't need to add NEW dynamic properties to a figure, we restore old ones

            qWarning() << "FigureXMLSerializer::readFigureRecursively() : Property" << propertyName <<
                          "of " << figure->objectName() << "parsing error (was added as a dynamic one)";

            return ObjectError;
        }
    }



    return Success;
}
