#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QXmlStreamAttributes>
#include <QPointF>
#include <QSizeF>
#include <QUuid>

namespace diagramster
{

// Figure-based class use QObject tree as a tree structure (parents, children, ownership, etc)

// All Figure-based classes must:
// > have a Q_INVOKABLE constructor
// > have a virtual destructor
// > have a registered metatype (you can add registration code to FigureFactory::registerMetaTypes() for convenience)

class Figure : public QObject
{
    Q_OBJECT

    // Data that have to be serialized/deserialized
    // must be declared as Q_PROPERTY and be convertable to QString

    // List properties have to be defined as QStringList

    Q_PROPERTY(QUuid uid READ uid)

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY xChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY xChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY xChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    Q_INVOKABLE explicit Figure(const QString& name = QString(),
                                QObject* parent = Q_NULLPTR,
                                const QUuid &uid = QUuid());

    virtual ~Figure() {}

    // Default implementation of QObject does not allow to change
    // the order of children so m_orderIndex and sorted list of children are used
    QList<Figure*> figureChildren(bool sort = true) const;

    int  orderIndex() const;
    void setOrderIndex(int index);
    void clearOrderIndex();

    qreal x() const;
    void setX(const qreal &x);

    qreal y() const;
    void setY(const qreal &y);

    qreal width() const;
    void setWidth(const qreal &width);

    qreal height() const;
    void setHeight(const qreal &height);

    bool visible() const;
    void setVisible(bool visible);

    QUuid uid() const;

    constexpr static const char* OBJECT_NAME_PROPERTY_NAME = "objectName";
    constexpr static const char* UID_PROPERTY_NAME = "uid";

signals:
    void dataChanged();
    void orderIndexChanged();
    void childAdded(Figure* child);
    void childRemoved(Figure* child);

    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void visibleChanged();

protected:
    virtual void childEvent(QChildEvent *event) override;

private:
    static const int DEFAULT_ORDER_INDEX = 0;
    int m_orderIndex = DEFAULT_ORDER_INDEX;

    static bool orderIndexLessThan(Figure* id1, Figure* id2);

    qreal m_x = 0.0;
    qreal m_y = 0.0;
    qreal m_width = 0.0;
    qreal m_height = 0.0;
    bool m_visible = true;

    QUuid m_uid;
};

}

#endif // OBJECT_H
