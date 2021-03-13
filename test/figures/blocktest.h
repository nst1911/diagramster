#ifndef BLOCKTEST_H
#define BLOCKTEST_H

#include <QObject>
#include <QtTest/QtTest>

namespace diagramster {
namespace test {

class BlockTest : public QObject
{
    Q_OBJECT

private slots:
    void connectorToString();
    void connectorFromString();
    void fillSideWithConnectors();
};

}
}
#endif // BLOCKTEST_H
