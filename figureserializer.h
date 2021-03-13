#ifndef OBJECTSERIALIZER_H
#define OBJECTSERIALIZER_H

#include "figure.h"
#include <QByteArray>

namespace diagramster
{

class FigureSerializer
{
public:
    enum Result {
        Success,
        ParsingError,
        ObjectError
    };

    virtual ~FigureSerializer() {}

    virtual QByteArray serialize(Figure* object, Result* result = nullptr) = 0;
    virtual Figure*    deserialize(const QByteArray& bytes, Result* result = nullptr) = 0;
};

class FigureXMLSerializer : public FigureSerializer
{
public:
    virtual ~FigureXMLSerializer() {}

    virtual QByteArray serialize(Figure* object, Result* result = nullptr) override;
    virtual Figure*    deserialize(const QByteArray& bytes, Result* result = nullptr) override;

    constexpr static const char* FIGURE_ELEMENT_NAME = "figure";
    constexpr static const char* PROPERTY_LIST_ELEMENT_NAME = "element";

    constexpr static const char* FIGURE_TYPE_ATTRIBUTE_NAME = "type";
    constexpr static const char* FIGURE_NAME_ATTRIBUTE_NAME = "name";
    constexpr static const char* FIGURE_UID_ATTRIBUTE_NAME  = "uid";

private:
    enum ReadFromXmlBehaviour { Default, ReadChild };

    Result  writeFigureRecursively(Figure *object, QXmlStreamWriter *writer);
    Figure* readFigureRecursively(QXmlStreamReader *reader, Result* result, ReadFromXmlBehaviour behaviour = Default);

    Result  readProperty(QXmlStreamReader* reader, Figure* figure);
    Result  readListProperty() const;

};

}


#endif // OBJECTSERIALIZER_H
