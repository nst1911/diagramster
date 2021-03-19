#include "basicobjectserializertest.h"
#include "basicobjectserializer.h"

#include "figures/block.h"
#include "diagramtest.h"

void diagramster::test::BasicObjectSerializerTest::serializeXML()
{
    auto diagram = DiagramTest::diagramExample();
    BasicObjectSerializer* serializer = new BasicObjectXMLSerializer;
    BasicObjectSerializer::Result result;

    auto bytes = serializer->serialize(diagram, &result);

    qDebug() << qPrintable(bytes);
    QVERIFY(!bytes.isEmpty());
    QCOMPARE(result, BasicObjectSerializer::Result::Success);

    delete diagram;
    delete serializer;
}

void diagramster::test::BasicObjectSerializerTest::deserializeXML()
{
    auto diagram = DiagramTest::diagramExample();
    BasicObjectSerializer* serializer = new BasicObjectXMLSerializer;
    BasicObjectSerializer::Result result;

    auto bytes = serializer->serialize(diagram, &result);

    //qDebug() << qPrintable(bytes);
    QVERIFY(!bytes.isEmpty());
    QCOMPARE(result, BasicObjectSerializer::Result::Success);

    // Then we try to deserialize this

    auto _diagram = serializer->deserialize(bytes, &result);

    QCOMPARE(result, BasicObjectSerializer::Success);
    QVERIFY(_diagram);

    // Check every basic object in the hierarchy

    QVERIFY(diagram->isRecursivelyEqualTo(_diagram));
    QCOMPARE(diagram->uid(), _diagram->uid());

    auto _obj1 = _diagram->basicObjectChildren()[0];
    auto obj1  = diagram->basicObjectChildren()[0];
    QVERIFY(obj1->isRecursivelyEqualTo(_obj1));
    QCOMPARE(obj1->uid(), _obj1->uid());

    auto _obj2 = _diagram->basicObjectChildren()[1];
    auto obj2  = diagram->basicObjectChildren()[1];
    QVERIFY(obj2->isRecursivelyEqualTo(_obj2));
    QCOMPARE(obj2->uid(), _obj2->uid());

    auto _obj21 = _obj2->basicObjectChildren()[0];
    auto obj21  = obj2->basicObjectChildren()[0];
    QVERIFY(obj21->isRecursivelyEqualTo(_obj21));
    QCOMPARE(obj21->uid(), _obj21->uid());

    auto _obj22 = _obj2->basicObjectChildren()[1];
    auto obj22  = obj2->basicObjectChildren()[1];
    QVERIFY(obj22->isRecursivelyEqualTo(_obj22));
    QCOMPARE(obj22->uid(), _obj22->uid());

    auto _obj221 = _obj22->basicObjectChildren()[0];
    auto obj221  = obj22->basicObjectChildren()[0];
    QVERIFY(obj221->isRecursivelyEqualTo(_obj221));
    QCOMPARE(obj221->uid(), _obj221->uid());

    auto _obj3 = _diagram->basicObjectChildren()[2];
    auto obj3  = diagram->basicObjectChildren()[2];
    QVERIFY(obj3->isRecursivelyEqualTo(_obj3));
    QCOMPARE(obj3->uid(), _obj3->uid());

    delete diagram;
    delete _diagram;
    delete serializer;
}
