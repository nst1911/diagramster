#include "blocktest.h"

#include "figures/block.h"

void diagramster::test::BlockTest::connectorToString()
{
    Block* block = new Block("block");
    block->addConnector(Block::Left, 0);
    block->addConnector(Block::Right, 0.5);
    block->addConnector(Block::Top, 1);
    block->addConnector(Block::Bottom, 0.33);

    QCOMPARE(block->connectorCount(), 4);

    for (auto connector : block->connectors())
        qDebug() << Block::Connector::toString(connector);

    delete block;
}

void diagramster::test::BlockTest::connectorFromString()
{
    Block* block = new Block("block");

    block->addConnector(block->uid().toString() + " 0 0 Left");
    block->addConnector(block->uid().toString() + " 1 0.5 Right");
    block->addConnector(block->uid().toString() + " 1 1 Top"); // This one will be rewrited with next connector since they have the same id
    block->addConnector(block->uid().toString() + " 2 0.33 Bottom");

    QCOMPARE(block->connectorCount(), 3);

    QCOMPARE(block->connector(0)->block(), block);
    QCOMPARE(block->connector(0)->side(), Block::Left);
    QCOMPARE(block->connector(0)->id(), 0);
    QCOMPARE(block->connector(0)->relativePos(), 0.0);

    QCOMPARE(block->connector(1)->block(), block);
    QCOMPARE(block->connector(1)->side(), Block::Top);
    QCOMPARE(block->connector(1)->id(), 1);
    QCOMPARE(block->connector(1)->relativePos(), 1.0);

    QCOMPARE(block->connector(2)->block(), block);
    QCOMPARE(block->connector(2)->side(), Block::Bottom);
    QCOMPARE(block->connector(2)->id(), 2);
    QCOMPARE(block->connector(2)->relativePos(), 0.33);

    Block* block2 = new Block("abcdef abcdef abcdef");
    block2->addConnector(block->uid().toString() + "0 0 Left");   // Wrong block uid is here (invalid connector)
    QCOMPARE(block2->connectorCount(), 0);                        // Size has not been changed

    delete block;
    delete block2;
}

void diagramster::test::BlockTest::fillSideWithConnectors()
{
    Block* block = new Block("block");

    block->fillSideWithConnectors(Block::Top, 3);

    QCOMPARE(block->connector(0)->block(), block);
    QCOMPARE(block->connector(0)->side(), Block::Top);
    QCOMPARE(block->connector(0)->id(), 0);
    QCOMPARE(block->connector(0)->relativePos(), 0.0);

    QCOMPARE(block->connector(1)->block(), block);
    QCOMPARE(block->connector(1)->side(), Block::Top);
    QCOMPARE(block->connector(1)->id(), 1);
    QCOMPARE(block->connector(1)->relativePos(), 0.5);

    QCOMPARE(block->connector(2)->block(), block);
    QCOMPARE(block->connector(2)->side(), Block::Top);
    QCOMPARE(block->connector(2)->id(), 2);
    QCOMPARE(block->connector(2)->relativePos(), 1.0);

    delete block;
}
