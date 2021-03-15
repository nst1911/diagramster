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
    void childrenSignalsTest();

    void isEqualTo();
    void isRecursivelyEqualTo();
};

}
}

#endif // FIGURETEST_H
