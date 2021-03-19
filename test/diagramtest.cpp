#include "diagramtest.h"
#include "figure.h"
#include "figures/block.h"
#include "figures/connectionline.h"

diagramster::Diagram *diagramster::test::DiagramTest::diagramExample()
{
    //              diagram
    //         |       |         |
    //      obj1     obj2       obj3
    //             |      |
    //           obj21   obj22
    //                     |
    //                   obj221


    Diagram* diagram = new Diagram("diagram");
    diagram->setWidth(1.0);
    diagram->setHeight(1.0);

    auto obj1 = new Block("obj1", diagram);
    obj1->setX(2.0);
    obj1->setY(2.0);
    obj1->setWidth(2.0);
    obj1->setHeight(2.0);
    obj1->setStrokeWidth(2);
    obj1->setStrokeColor(QColor("blue"));
    obj1->addConnector(Block::Right, 0);
    obj1->addConnector(Block::Bottom, 0.33);

    auto obj2 = new Block("obj2", diagram);
    obj2->setX(3.0);
    obj2->setY(3.0);
    obj2->setWidth(3.0);
    obj2->setHeight(3.0);
    obj2->setStrokeWidth(3);
    obj2->setStrokeColor(QColor("red"));
    obj2->addConnector(Block::Left, 0);
    obj2->addConnector(Block::Top, 0.33);

    auto obj21 = new Figure("obj21", obj2);
    obj21->setX(4.0);
    obj21->setY(4.0);
    obj21->setWidth(4.0);
    obj21->setHeight(4.0);

    auto obj22 = new Figure("obj22", obj2);
    obj22->setX(5.0);
    obj22->setY(5.0);
    obj22->setWidth(5.0);
    obj22->setHeight(5.0);

    auto obj221 = new Figure("obj221", obj22);
    obj221->setX(6.0);
    obj221->setY(6.0);
    obj221->setWidth(6.0);
    obj221->setHeight(6.0);

    auto obj3 = new ConnectionLine("obj3", diagram);
    obj3->setX(7.0);
    obj3->setY(7.0);
    obj3->setWidth(7.0);
    obj3->setHeight(7.0);
    obj3->setStartBlock(obj1);
    obj3->setStartBlockConnectorId(0);
    obj3->setEndBlock(obj2);
    obj3->setEndBlockConnectorId(0);

    return diagram;
}
