#ifndef FIGURETEST_H
#define FIGURETEST_H

#include <QObject>
#include <QtTest/QtTest>

namespace diagramster {
namespace test {

class FigureTest : public QObject
{
    Q_OBJECT

private slots:
    void figureChildren();
    //void toXml();
    //void fromXml();
    void childrenSignalsTest();
};

}
}

#endif // FIGURETEST_H
