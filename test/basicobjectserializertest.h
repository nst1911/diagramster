#ifndef FIGURESERIALIZERTEST_H
#define FIGURESERIALIZERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "figure.h"

namespace diagramster {
namespace test {

class BasicObjectSerializerTest : public QObject
{
    Q_OBJECT

private slots:
    void serializeXML();
    void deserializeXML();
};

}
}

#endif // FIGURESERIALIZERTEST_H
