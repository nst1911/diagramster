#include "connectionlinetest.h"
#include "diagram.h"
#include "figures/connectionline.h"

void diagramster::test::ConnectionLineTest::isValid()
{
    auto diagram = new Diagram("diagram");

    auto block1 = new Block("block1", diagram);
    block1->addConnector(Block::Left, 0);
    block1->addConnector(Block::Top, 0.33);

    auto block2 = new Block("block2", diagram);
    block2->addConnector(Block::Right, 0);
    block2->addConnector(Block::Bottom, 0.33);

    auto block3 = new Block("block3", diagram);

    auto line = new ConnectionLine("line", diagram);

    line->setStartBlock(block1, 0);
    line->setEndBlock(block2, 0);
    QVERIFY(line->isValid());

    line->setStartBlock(block1, 1);
    line->setEndBlock(block2, 1);
    QVERIFY(line->isValid());

    line->setStartBlock(block1, 2);
    line->setEndBlock(block2, 2);
    QVERIFY(!line->isValid());

    line->setStartBlock(block1, 0);
    line->setEndBlock(block3, 0);
    QVERIFY(!line->isValid());

    line->setStartBlock(nullptr);
    line->setEndBlock(block2, 0);
    QVERIFY(!line->isValid());

    delete diagram;
}

void diagramster::test::ConnectionLineTest::setBlockUid()
{
    // Diagram 1
    auto _diagram = new Diagram("diagram");

    auto _block1 = new Block("block1", _diagram);
    _block1->addConnector(Block::Left, 0);
    _block1->addConnector(Block::Top, 0.33);

    // Diagram 2
    auto diagram = new Diagram("diagram");

    auto block1 = new Block("block1", diagram);
    block1->addConnector(Block::Left, 0);
    block1->addConnector(Block::Top, 0.33);

    auto block2 = new Block("block2", diagram);
    block2->addConnector(Block::Right, 0);
    block2->addConnector(Block::Bottom, 0.33);

    auto block3 = new Block("block3", diagram);
    block2->addConnector(Block::Right, 0);
    block2->addConnector(Block::Bottom, 0.33);

    auto block4 = new Block("block4", block3);
    block2->addConnector(Block::Right, 0);
    block2->addConnector(Block::Bottom, 0.33);

    auto line = new ConnectionLine("line", diagram);

    line->setStartBlockUid(block1->uid());
    line->setEndBlockUid(block2->uid());

    QCOMPARE(line->startBlock(), block1);
    QCOMPARE(line->endBlock(), block2);

    line->setStartBlockUid(block4->uid());
    QCOMPARE(line->startBlock(), block4);

    line->setStartBlockUid(_block1->uid()); // Different diagrams
    QCOMPARE(line->startBlock(), block4);

    line->setStartBlockUid(diagram->uid()); // Not a block
    QCOMPARE(line->startBlock(), block4);

    delete diagram;
    delete _diagram;
}
