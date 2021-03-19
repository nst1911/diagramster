#ifndef OBJECTSERIALIZER_H
#define OBJECTSERIALIZER_H

#include "figure.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QByteArray>

// TODO: FigureSerializer -> BasicObjectSerializer

namespace diagramster
{

class BasicObjectSerializer
{
public:
    enum Result {
        Success,
        ParsingError,
        ObjectError
    };

    virtual ~BasicObjectSerializer() {}

    virtual QByteArray   serialize(BasicObject* object, Result* result = nullptr) = 0;
    virtual BasicObject* deserialize(const QByteArray& bytes, Result* result = nullptr) = 0;
};

class BasicObjectXMLSerializer : public BasicObjectSerializer
{
public:
    virtual ~BasicObjectXMLSerializer() {}

    virtual QByteArray   serialize(BasicObject* object, Result* result = nullptr) override;
    virtual BasicObject* deserialize(const QByteArray& bytes, Result* result = nullptr) override;

    constexpr static const char* BASIC_OBJECT_ELEMENT_NAME = "object";
    constexpr static const char* PROPERTY_LIST_ELEMENT_NAME = "element";

    constexpr static const char* TYPE_ATTRIBUTE_NAME = "type";
    constexpr static const char* OBJECT_NAME_ATTRIBUTE_NAME = "name";
    constexpr static const char* UID_ATTRIBUTE_NAME  = "uid";

private:
    enum ReadFromXmlBehaviour { Default, ReadChild };

    struct ParsedPropertyData {
        BasicObject* object;
        QString  propertyName;
        QVariant propertyValue;
        Result   result;
    };

    Result  writeBasicObjectRecursively(BasicObject *object, QXmlStreamWriter *writer);

    BasicObject* readBasicObjectRecursively(QXmlStreamReader *reader,
                                            Result* result,
                                            QList<ParsedPropertyData> *propertyData,
                                            ReadFromXmlBehaviour behaviour = Default);

    ParsedPropertyData readProperty(QXmlStreamReader* reader, BasicObject* figure);

};

}


#endif // OBJECTSERIALIZER_H
