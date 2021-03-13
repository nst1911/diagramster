#include "figureserializertest.h"
#include "figureserializer.h"

#include "figures/block.h"

diagramster::Figure *diagramster::test::FigureSerializerTest::figureHierarchy()
{
    //                obj
    //         |       |         |
    //      obj1     obj2       obj3
    //             |      |
    //           obj21   obj22
    //                     |
    //                   obj221


    Figure* obj = new Figure("obj"); 
    obj->setX(1.0);
    obj->setY(1.0);
    obj->setWidth(1.0);
    obj->setHeight(1.0);

    Figure* obj1 = new Figure("obj1", obj);
    obj1->setX(2.0);
    obj1->setY(2.0);
    obj1->setWidth(2.0);
    obj1->setHeight(2.0);

    Block* obj2 = new Block("obj2", obj);
    obj2->setX(3.0);
    obj2->setY(3.0);
    obj2->setWidth(3.0);
    obj2->setHeight(3.0);
    obj2->setStrokeWidth(3);
    obj2->setStrokeColor(QColor("red"));
    obj2->addConnector(Block::Left, 0);
    obj2->addConnector(Block::Top, 0.33);

    Figure* obj21 = new Figure("obj21", obj2);
    obj21->setX(4.0);
    obj21->setY(4.0);
    obj21->setWidth(4.0);
    obj21->setHeight(4.0);

    Figure* obj22 = new Figure("obj22", obj2);
    obj22->setX(5.0);
    obj22->setY(5.0);
    obj22->setWidth(5.0);
    obj22->setHeight(5.0);

    Figure* obj221 = new Figure("obj221", obj22);
    obj221->setX(6.0);
    obj221->setY(6.0);
    obj221->setWidth(6.0);
    obj221->setHeight(6.0);

    Figure* obj3 = new Figure("obj3", obj);
    obj3->setX(7.0);
    obj3->setY(7.0);
    obj3->setWidth(7.0);
    obj3->setHeight(7.0);

    return obj;
}

void diagramster::test::FigureSerializerTest::serializeXML()
{
    Figure* obj = figureHierarchy();
    FigureSerializer* serializer = new FigureXMLSerializer;
    FigureSerializer::Result result;

    auto bytes = serializer->serialize(obj, &result);

    qDebug() << qPrintable(bytes);
    QCOMPARE(result, FigureSerializer::Result::Success);

    delete obj;
    delete serializer;
}

void diagramster::test::FigureSerializerTest::deserializeXML()
{
    Figure* obj = figureHierarchy();
    FigureSerializer* serializer = new FigureXMLSerializer;
    FigureSerializer::Result result;

    auto bytes = serializer->serialize(obj, &result);

    //qDebug() << qPrintable(bytes);
    QVERIFY(!bytes.isEmpty());
    QCOMPARE(result, FigureSerializer::Result::Success);

    // Then we try to deserialize this

    Figure* _obj = serializer->deserialize(bytes, &result);

    QCOMPARE(result, FigureSerializer::Success);
    QVERIFY(_obj);

    // Check every figure in the hierarchy

    QCOMPARE(_obj->objectName(),                obj->objectName());
    QCOMPARE(_obj->figureChildren().size(),     obj->figureChildren().size());
    QCOMPARE(_obj->x(),                         obj->x());
    QCOMPARE(_obj->y(),                         obj->y());
    QCOMPARE(_obj->width(),                     obj->width());
    QCOMPARE(_obj->height(),                    obj->height());
    QCOMPARE(_obj->uid(),                       obj->uid());


    auto _obj1 = _obj->figureChildren()[0];
    auto obj1  = obj->figureChildren()[0];
    QCOMPARE(_obj1->objectName(),               obj1->objectName());
    QCOMPARE(_obj1->figureChildren().size(),    obj1->figureChildren().size());
    QCOMPARE(_obj1->x(),                        obj1->x());
    QCOMPARE(_obj1->y(),                        obj1->y());
    QCOMPARE(_obj1->width(),                    obj1->width());
    QCOMPARE(_obj1->height(),                   obj1->height());
    QCOMPARE(_obj1->uid(),                      obj1->uid());


    auto _obj2 = dynamic_cast<Block*>(_obj->figureChildren()[1]);
    auto obj2  = dynamic_cast<Block*>(obj->figureChildren()[1]);
    QVERIFY(_obj2 && obj2);
    QCOMPARE(_obj2->objectName(),               obj2->objectName());
    QCOMPARE(_obj2->figureChildren().size(),    obj2->figureChildren().size());
    QCOMPARE(_obj2->x(),                        obj2->x());
    QCOMPARE(_obj2->y(),                        obj2->y());
    QCOMPARE(_obj2->width(),                    obj2->width());
    QCOMPARE(_obj2->height(),                   obj2->height());
    QCOMPARE(_obj2->uid(),                      obj2->uid());
    QCOMPARE(_obj2->strokeWidth(),              obj2->strokeWidth());
    QCOMPARE(_obj2->strokeColor(),              obj2->strokeColor());
    QCOMPARE(_obj2->connector(0)->block(),      _obj2);
    QCOMPARE(_obj2->connector(0)->side(),       obj2->connector(0)->side());
    QCOMPARE(_obj2->connector(0)->id(),         obj2->connector(0)->id());
    QCOMPARE(_obj2->connector(0)->relativePos(), obj2->connector(0)->relativePos());
    QCOMPARE(_obj2->connector(1)->block(),      _obj2);
    QCOMPARE(_obj2->connector(1)->side(),       obj2->connector(1)->side());
    QCOMPARE(_obj2->connector(1)->id(),         obj2->connector(1)->id());
    QCOMPARE(_obj2->connector(1)->relativePos(), obj2->connector(1)->relativePos());

    auto _obj21 = _obj2->figureChildren()[0];
    auto obj21  = obj2->figureChildren()[0];
    QCOMPARE(_obj21->objectName(),               obj21->objectName());
    QCOMPARE(_obj21->figureChildren().size(),    obj21->figureChildren().size());
    QCOMPARE(_obj21->x(),                        obj21->x());
    QCOMPARE(_obj21->y(),                        obj21->y());
    QCOMPARE(_obj21->width(),                    obj21->width());
    QCOMPARE(_obj21->height(),                   obj21->height());
    QCOMPARE(_obj21->uid(),                      obj21->uid());

    auto _obj22 = _obj2->figureChildren()[1];
    auto obj22  = obj2->figureChildren()[1];
    QCOMPARE(_obj22->objectName(),               obj22->objectName());
    QCOMPARE(_obj22->figureChildren().size(),    obj22->figureChildren().size());
    QCOMPARE(_obj22->x(),                        obj22->x());
    QCOMPARE(_obj22->y(),                        obj22->y());
    QCOMPARE(_obj22->width(),                    obj22->width());
    QCOMPARE(_obj22->height(),                   obj22->height());
    QCOMPARE(_obj22->uid(),                      obj22->uid());


    auto _obj221 = _obj22->figureChildren()[0];
    auto obj221  = obj22->figureChildren()[0];
    QCOMPARE(_obj221->objectName(),               obj221->objectName());
    QCOMPARE(_obj221->figureChildren().size(),    obj221->figureChildren().size());
    QCOMPARE(_obj221->x(),                        obj221->x());
    QCOMPARE(_obj221->y(),                        obj221->y());
    QCOMPARE(_obj221->width(),                    obj221->width());
    QCOMPARE(_obj221->height(),                   obj221->height());
    QCOMPARE(_obj221->uid(),                      obj221->uid());


    auto _obj3 = _obj->figureChildren()[2];
    auto obj3  = obj->figureChildren()[2];
    QCOMPARE(_obj3->objectName(),               obj3->objectName());
    QCOMPARE(_obj3->figureChildren().size(),    obj3->figureChildren().size());
    QCOMPARE(_obj3->x(),                        obj3->x());
    QCOMPARE(_obj3->y(),                        obj3->y());
    QCOMPARE(_obj3->width(),                    obj3->width());
    QCOMPARE(_obj3->height(),                   obj3->height());
    QCOMPARE(_obj3->uid(),                      obj3->uid());

    delete obj;
    delete _obj;
    delete serializer;
}
