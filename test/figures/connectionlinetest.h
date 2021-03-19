#ifndef CONNECTIONLINETEST_H
#define CONNECTIONLINETEST_H


#include <QObject>
#include <QtTest/QtTest>

namespace diagramster {
namespace test {

class ConnectionLineTest : public QObject
{
    Q_OBJECT

private slots:
    void isValid();
    void setBlockUid();
};

}
}
#endif // CONNECTIONLINETEST_H
