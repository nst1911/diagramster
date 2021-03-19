#ifndef TESTS_H
#define TESTS_H

#include "test/figuretest.h"
#include "test/basicobjectserializertest.h"
#include "test/figures/blocktest.h"
#include "test/basicobjecttest.h"
#include "test/figures/connectionlinetest.h"

namespace diagramster {
namespace test {

void execUnitTests(int argc, char* argv[])
{
    BasicObjectTest basicObjectTest;
    QTest::qExec(&basicObjectTest, argc, argv);

    BasicObjectSerializerTest figureSerializerTest;
    QTest::qExec(&figureSerializerTest, argc, argv); 

    FigureTest figureTest;
    QTest::qExec(&figureTest, argc, argv);

    BlockTest blockTest;
    QTest::qExec(&blockTest, argc, argv);

    ConnectionLineTest connectionLineTest;
    QTest::qExec(&connectionLineTest, argc, argv);
}

}
}

#endif // TESTS_H
