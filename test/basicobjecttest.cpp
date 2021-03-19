#include "basicobjecttest.h"
#include "basicobject.h"

void diagramster::test::BasicObjectTest::childrenSignalsTest()
{
    BasicObject* obj = new BasicObject("obj");
    QSignalSpy obj_add_spy(obj, SIGNAL(childAdded(BasicObject*)));
    QSignalSpy obj_remove_spy(obj, SIGNAL(childRemoved(BasicObject*)));

    // Test setParent()
    BasicObject* obj1 = new BasicObject("obj1");
    BasicObject* obj2 = new BasicObject("obj2");

    obj1->setParent(obj);  // obj = [obj1]
    obj2->setParent(obj);  // obj = [obj1, obj2]

    QCOMPARE(obj_add_spy.count(), 2);

    obj2->setParent(nullptr); // obj = [obj1]
    delete obj2;

    QCOMPARE(obj_remove_spy.count(), 1);

    // Test setParent() via constructor
    BasicObject* obj3 = new BasicObject("obj3", obj); // obj = [obj1, obj3]
    QCOMPARE(obj_add_spy.count(), 3);

    // Add not-BasicObject object
    QObject* _obj4 = new QObject(obj); // obj = [obj1, obj3, _obj4]
    QObject* _obj5 = new QObject;      // obj = [obj1, obj3, _obj4, _obj5]
    _obj5->setParent(obj);

    QCOMPARE(obj_add_spy.count(), 3);               // No new signals

    // Test BasicObject convenience functions
    obj->appendBasicObjectChild(new BasicObject("obj6"));       // obj = [obj1, obj3, _obj4, _obj5, obj6]
    obj->prependBasicObjectChild(new BasicObject("obj7"));      // obj = [obj1, obj3, _obj4, _obj5, obj6, obj7]
    obj->insertBasicObjectChild(1, new BasicObject("obj8"));    // obj = [obj1, obj3, _obj4, _obj5, obj6, obj7, obj8]
    obj->appendChild(new BasicObject("obj9"));                  // obj = [obj1, obj3, _obj4, _obj5, obj6, obj7, obj8, obj9]

    auto _obj10 = new QObject;
    obj->appendChild(_obj10); // No signal                      // obj = [obj1, obj3, _obj4, _obj5, obj6, obj7, obj8, obj9, _obj10]

    QCOMPARE(obj_add_spy.count(), 7);

    obj->removeChild(obj1);                  // obj = [obj3, _obj4, _obj5, obj6, obj7, obj8, obj9, _obj10]
    obj->removeChild(_obj5); // No signal    // obj = [obj3, _obj4, obj6, obj7, obj8, obj9, _obj10]

    QCOMPARE(obj_remove_spy.count(), 2);

    obj->clearChildren();                   // obj = []
    QCOMPARE(obj_remove_spy.count(), 7);

    obj->appendChild(new QObject);      // obj = [_obj11]
    obj->appendChild(new BasicObject);  // obj = [_obj11, obj12]
    obj->clearBasicObjectChildren();

    QCOMPARE(obj_remove_spy.count(), 8);

    delete obj;

    Q_UNUSED(obj3);
    Q_UNUSED(_obj4);
}

void diagramster::test::BasicObjectTest::basicObjectChildren()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);
    auto obj4 = new QObject(obj);
    auto obj5 = new BasicObject("obj5", obj);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 4);
    QCOMPARE(basicObjects[0], obj1);
    QCOMPARE(basicObjects[1], obj2);
    QCOMPARE(basicObjects[2], obj3);
    QCOMPARE(basicObjects[3], obj5);

    Q_UNUSED(obj4);
    delete obj;
}

void diagramster::test::BasicObjectTest::insertBasicObjectChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);
    auto obj4 = new BasicObject("obj4");

    obj->insertBasicObjectChild(1, obj4);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 4);
    QCOMPARE(basicObjects[0], obj1);
    QCOMPARE(basicObjects[1], obj4);
    QCOMPARE(basicObjects[2], obj2);
    QCOMPARE(basicObjects[3], obj3);

    auto obj5 = new BasicObject("obj5");
    obj->insertBasicObjectChild(-5, obj4); // Invalid indexes
    obj->insertBasicObjectChild(10, obj4);

    basicObjects = obj->basicObjectChildren(); // No changes
    QCOMPARE(basicObjects.size(), 4);
    QCOMPARE(basicObjects[0], obj1);
    QCOMPARE(basicObjects[1], obj4);
    QCOMPARE(basicObjects[2], obj2);
    QCOMPARE(basicObjects[3], obj3);

    Q_UNUSED(obj5);
    delete obj;
}

void diagramster::test::BasicObjectTest::appendBasicObjectChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3");

    obj->appendBasicObjectChild(obj3);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 3);
    QCOMPARE(basicObjects[0], obj1);
    QCOMPARE(basicObjects[1], obj2);
    QCOMPARE(basicObjects[2], obj3);

    obj->appendBasicObjectChild(nullptr);
    QCOMPARE(basicObjects.size(), 3); // No changes

    delete obj;
}

void diagramster::test::BasicObjectTest::prependBasicObjectChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3");

    obj->prependBasicObjectChild(obj3);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 3);
    QCOMPARE(basicObjects[0], obj3);
    QCOMPARE(basicObjects[1], obj1);
    QCOMPARE(basicObjects[2], obj2);

    obj->prependBasicObjectChild(nullptr);
    QCOMPARE(basicObjects.size(), 3); // No changes

    delete obj;
}

void diagramster::test::BasicObjectTest::moveBasicObjectChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);

    obj->moveBasicObjectChild(2, 1);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 3);
    QCOMPARE(basicObjects[0], obj1);
    QCOMPARE(basicObjects[1], obj3);
    QCOMPARE(basicObjects[2], obj2);

    obj->moveBasicObjectChild(obj1, 1);

    basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 3);
    QCOMPARE(basicObjects[0], obj3);
    QCOMPARE(basicObjects[1], obj1);
    QCOMPARE(basicObjects[2], obj2);

    auto obj11 = new BasicObject("obj11", obj1);
    obj->moveBasicObjectChild(obj11, 1); // obj11 is not child of obj

    basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 3);    // No changes
    QCOMPARE(basicObjects[0], obj3);
    QCOMPARE(basicObjects[1], obj1);
    QCOMPARE(basicObjects[2], obj2);

    delete obj;
}

void diagramster::test::BasicObjectTest::appendChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new QObject(obj);
    auto obj3 = new BasicObject("obj3");

    obj->appendChild(obj2);
    obj->appendChild(obj3);

    auto objects = obj->children();
    QCOMPARE(objects.size(), 3);
    QCOMPARE(objects[0], obj1);
    QCOMPARE(objects[1], obj2);
    QCOMPARE(objects[2], obj3);

    delete obj;
}

void diagramster::test::BasicObjectTest::removeChild()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);

    obj->removeChild(obj1);

    auto basicObjects = obj->basicObjectChildren();
    QCOMPARE(basicObjects.size(), 2);
    QCOMPARE(basicObjects[0], obj2);
    QCOMPARE(basicObjects[1], obj3);

    obj->removeChild(obj1);                     // Try to remove it again
    basicObjects = obj->basicObjectChildren();  // No changes
    QCOMPARE(basicObjects.size(), 2);
    QCOMPARE(basicObjects[0], obj2);
    QCOMPARE(basicObjects[1], obj3);

    auto obj22 = new BasicObject("obj22", obj2);
    obj->removeChild(obj22);                    // obj22 is not child of obj
    basicObjects = obj->basicObjectChildren();  // No changes
    QCOMPARE(basicObjects.size(), 2);
    QCOMPARE(basicObjects[0], obj2);
    QCOMPARE(basicObjects[1], obj3);

    delete obj;
}

void diagramster::test::BasicObjectTest::clearChildren()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);
    auto obj4 = new QObject(obj);

    obj->clearChildren();

    auto children = obj->children();
    auto basicObjects = obj->basicObjectChildren();

    QVERIFY(children.isEmpty() && basicObjects.isEmpty());

    Q_UNUSED(obj1);
    Q_UNUSED(obj2);
    Q_UNUSED(obj3);
    Q_UNUSED(obj4);
    delete obj;
}

void diagramster::test::BasicObjectTest::clearBasicObjectChildren()
{
    auto obj  = new BasicObject("obj");
    auto obj1 = new BasicObject("obj1", obj);
    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);
    auto obj4 = new QObject(obj);

    obj->clearBasicObjectChildren();

    auto children = obj->children();
    auto basicObjects = obj->basicObjectChildren();

    QVERIFY(basicObjects.isEmpty());
    QCOMPARE(children.size(), 1);

    Q_UNUSED(obj1);
    Q_UNUSED(obj2);
    Q_UNUSED(obj3);
    Q_UNUSED(obj4);
    delete obj;
}

void diagramster::test::BasicObjectTest::findBasicObjectChild()
{
    auto obj = new BasicObject("obj");

    auto obj1 = new BasicObject("obj1", obj);
    auto obj11 = new BasicObject("obj11", obj1);
    auto obj12 = new BasicObject("obj12", obj1);
    auto obj121 = new BasicObject("obj121", obj11);

    auto obj2 = new BasicObject("obj2", obj);
    auto obj3 = new BasicObject("obj3", obj);
    auto obj4 = new BasicObject("obj4");

    QCOMPARE(obj->findBasicObjectChild(obj121->uid(), Qt::FindDirectChildrenOnly), nullptr);
    QCOMPARE(obj->findBasicObjectChild(obj121->uid(), Qt::FindChildrenRecursively), obj121);
    QCOMPARE(obj->findBasicObjectChild(obj121->uid()), obj121);
    QCOMPARE(obj->findBasicObjectChild(obj4->uid(), Qt::FindDirectChildrenOnly),  nullptr);
    QCOMPARE(obj->findBasicObjectChild(obj4->uid(), Qt::FindChildrenRecursively), nullptr);

    Q_UNUSED(obj12);
    Q_UNUSED(obj2);
    Q_UNUSED(obj3);

    delete obj;
}

void diagramster::test::BasicObjectTest::isEqualTo()
{
    auto obj1 = new BasicObject("obj1");
    auto obj11 = new BasicObject("obj11");
    obj11->setParent(obj1);

    auto obj2 = new BasicObject("obj1");     // Same name, but different children
    auto obj21 = new BasicObject("obj11");
    auto obj22 = new BasicObject("obj11");
    obj21->setParent(obj2);
    obj22->setParent(obj2);

    auto obj3 = new BasicObject("obj2");    // Different name

    QVERIFY(obj1->isEqualTo(obj1));
    QVERIFY(obj1->isEqualTo(obj2));
    QVERIFY(!obj1->isEqualTo(obj3));

    delete obj1;
    delete obj2;
    delete obj3;
}

void diagramster::test::BasicObjectTest::isRecursivelyEqualTo()
{
    auto obj1 = new BasicObject("obj1");
    auto obj11 = new BasicObject("obj11");
    obj11->setParent(obj1);

    auto obj2 = new BasicObject("obj1");     // Same properties, but different children size
    auto obj21 = new BasicObject("obj11");
    auto obj22 = new BasicObject("obj11");
    obj21->setParent(obj2);
    obj22->setParent(obj2);

    auto obj3 = new BasicObject("obj1");     // Same properties and children
    auto obj31 = new BasicObject("obj11");
    obj31->setParent(obj3);

    auto obj4 = new BasicObject("obj2");     // Different properties

    auto obj5 = new BasicObject("obj1");     // Different children properties (name)
    auto obj51 = new BasicObject("obj51");
    obj51->setParent(obj5);

    QVERIFY(obj1->isRecursivelyEqualTo(obj1));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj2));
    QVERIFY(obj1->isRecursivelyEqualTo(obj3));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj4));
    QVERIFY(!obj1->isRecursivelyEqualTo(obj5));

    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    delete obj5;
}
