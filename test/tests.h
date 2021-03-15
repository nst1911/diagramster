#ifndef TESTS_H
#define TESTS_H

#include "test/figuretest.h"
#include "test/basicobjectserializertest.h"
#include "test/figures/blocktest.h"
#include "test/basicobjecttest.h"

namespace diagramster {
namespace test {

void execUnitTests(int argc, char* argv[])
{
    BasicObjectTest basicObjectTest;
    QTest::qExec(&basicObjectTest, argc, argv);

    FigureTest figureTest;
    QTest::qExec(&figureTest, argc, argv);

    BasicObjectSerializerTest figureSerializerTest;
    QTest::qExec(&figureSerializerTest, argc, argv);

    BlockTest blockTest;
    QTest::qExec(&blockTest, argc, argv);
}

}
}

#endif // TESTS_H
