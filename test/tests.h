#ifndef TESTS_H
#define TESTS_H

#include "test/figuretest.h"
#include "test/figureserializertest.h"
#include "test/figures/blocktest.h"

namespace diagramster {
namespace test {

void execUnitTests(int argc, char* argv[])
{
    FigureTest figureTest;
    QTest::qExec(&figureTest, argc, argv);

    FigureSerializerTest figureSerializerTest;
    QTest::qExec(&figureSerializerTest, argc, argv);

    BlockTest blockTest;
    QTest::qExec(&blockTest, argc, argv);
}

}
}

#endif // TESTS_H
