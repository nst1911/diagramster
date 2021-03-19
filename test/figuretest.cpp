#include "figuretest.h"
#include "figure.h"
#include <QSignalSpy>

//void diagramster::test::FigureTest::childrenSignalsTest()
//{
//    Figure* obj = new Figure("obj");
//    Figure* obj1 = new Figure("obj1");
//    Figure* obj2 = new Figure("obj2");
//    Figure* obj21 = new Figure("obj21");
//    Figure* obj22 = new Figure("obj22");
//    Figure* obj221 = new Figure("obj221");

//    QSignalSpy obj_add_spy(obj, SIGNAL(childAdded(BasicObject*)));
//    QSignalSpy obj1_add_spy(obj1, SIGNAL(childAdded(BasicObject*)));
//    QSignalSpy obj2_add_spy(obj2, SIGNAL(childAdded(BasicObject*)));
//    QSignalSpy obj21_add_spy(obj21, SIGNAL(childAdded(BasicObject*)));
//    QSignalSpy obj22_add_spy(obj22, SIGNAL(childAdded(BasicObject*)));
//    QSignalSpy obj221_add_spy(obj221, SIGNAL(childAdded(BasicObject*)));

//    obj1->setParent(obj);
//    obj2->setParent(obj);
//    obj21->setParent(obj2);
//    obj22->setParent(obj2);
//    obj221->setParent(obj22);

//    QCOMPARE(obj22_add_spy.count(), 1);
//    QCOMPARE(obj2_add_spy.count(), 2);
//    QCOMPARE(obj_add_spy.count(), 2);

//    QSignalSpy obj22_remove_spy(obj22, SIGNAL(childRemoved(BasicObject*)));

//    obj221->setParent(nullptr);

//    QCOMPARE(obj22_remove_spy.count(), 1);

//    delete obj;
//    delete obj221;
//}

void diagramster::test::FigureTest::isEqualTo()
{
    Figure* obj = new Figure("obj");
    obj->setX(1.0);
    obj->setY(1.0);
    obj->setWidth(1.0);
    obj->setHeight(1.0);

    Figure* obj2 = new Figure("obj"); // Same
    obj2->setX(1.0);
    obj2->setY(1.0);
    obj2->setWidth(1.0);
    obj2->setHeight(1.0);

    Figure* obj3 = new Figure("objjjjjjjjjj"); // Different name
    obj3->setX(1.0);
    obj3->setY(1.0);
    obj3->setWidth(1.0);
    obj3->setHeight(1.0);

    Figure* obj4 = new Figure("obj"); // Different x,y
    obj4->setX(5.0);
    obj4->setY(5.0);
    obj4->setWidth(1.0);
    obj4->setHeight(1.0);

    QVERIFY(obj->isEqualTo(obj));
    QVERIFY(obj->isEqualTo(obj2));
    QVERIFY(!obj->isEqualTo(obj3));
    QVERIFY(!obj->isEqualTo(obj4));
}

void diagramster::test::FigureTest::isRecursivelyEqualTo()
{
    auto obj1 = new Figure("obj1");
    auto obj11 = new Figure("obj11");
    obj11->setParent(obj1);

    auto obj2 = new Figure("obj1");     // Same properties, but different children size
    auto obj21 = new Figure("obj11");
    auto obj22 = new Figure("obj11");
    obj21->setParent(obj2);
    obj22->setParent(obj2);

    auto obj3 = new Figure("obj1");     // Same properties and children
    auto obj31 = new Figure("obj11");
    obj31->setParent(obj3);

    auto obj4 = new Figure("obj1");     // Different properties
    obj4->setHeight(55.125);

    auto obj5 = new Figure("obj1");     // Different children properties (name)
    auto obj51 = new Figure("obj51");
    obj51->setParent(obj5);
    obj51->setHeight(55.125);

    QVERIFY(obj1->isRecursivelyEqualTo(obj1));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj2));
    QVERIFY(obj1->isRecursivelyEqualTo(obj3));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj4));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj5));
}
