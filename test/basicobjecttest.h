#ifndef BASICOBJECTTEST_H
#define BASICOBJECTTEST_H

#include <QObject>
#include <QtTest/QtTest>

namespace diagramster {
namespace test {

class BasicObjectTest : public QObject
{
    Q_OBJECT

private slots:
    void childrenSignalsTest();

    void basicObjectChildren();

    void insertBasicObjectChild();
    void appendBasicObjectChild();
    void prependBasicObjectChild();
    void moveBasicObjectChild();

    void appendChild();
    void removeChild();
    void clearChildren();
    void clearBasicObjectChildren();

    void findBasicObjectChild();

    void isEqualTo();
    void isRecursivelyEqualTo();
};

}
}

#endif // BASICOBJECTTEST_H
