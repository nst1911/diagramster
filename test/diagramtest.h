#ifndef DIAGRAMTEST_H
#define DIAGRAMTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "diagram.h"

namespace diagramster {
namespace test {

class DiagramTest : public QObject
{
    Q_OBJECT

public:
    static Diagram *diagramExample();
};

}
}

#endif // DIAGRAMTEST_H
