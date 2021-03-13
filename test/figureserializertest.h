#ifndef FIGURESERIALIZERTEST_H
#define FIGURESERIALIZERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "figure.h"

namespace diagramster {
namespace test {

class FigureSerializerTest : public QObject
{
    Q_OBJECT

private:
    static Figure* figureHierarchy();
    //const static QByteArray FIGURE_HIERARCHY_SERIALIZED_DATA;

private slots:
    void serializeXML();
    void deserializeXML();
};

}
}

#endif // FIGURESERIALIZERTEST_H
