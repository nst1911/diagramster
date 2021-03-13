#include "figure.h"
#include <QChildEvent>
#include <QXmlStreamWriter>

diagramster::Figure::Figure(const QString &name, QObject *parent, const QUuid& uid)
    : QObject(parent),
      m_uid(uid.isNull() ? QUuid::createUuid() : uid)
{
    setObjectName(name);
}

QList<diagramster::Figure *> diagramster::Figure::figureChildren(bool sort) const
{
    QList<diagramster::Figure*> sorted;

    for (auto object : children())
        if (auto identity = qobject_cast<Figure*>(object))
            sorted << identity;

    if (sorted.size() > 1 && sort)
        std::sort(sorted.begin(), sorted.end(), orderIndexLessThan);

    return sorted;
}

int diagramster::Figure::orderIndex() const
{
    return m_orderIndex;
}

void diagramster::Figure::setOrderIndex(int index)
{
    if (m_orderIndex != index) {
        m_orderIndex = index;
        emit orderIndexChanged();
    }
}

void diagramster::Figure::clearOrderIndex()
{
    setOrderIndex(DEFAULT_ORDER_INDEX);
}

void diagramster::Figure::childEvent(QChildEvent *event)
{
    QObject::childEvent(event);

    auto identity = qobject_cast<Figure*>(event->child());
    if (!identity) return;

    if (event->added())
        emit childAdded(identity);

    if (event->removed())
        emit childRemoved(identity);
}

bool diagramster::Figure::orderIndexLessThan(diagramster::Figure *id1, diagramster::Figure *id2)
{
    return id1->orderIndex() < id2->orderIndex();
}

bool diagramster::Figure::visible() const
{
    return m_visible;
}

void diagramster::Figure::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        emit visibleChanged();
    }
}

QUuid diagramster::Figure::uid() const
{
    return m_uid;
}

qreal diagramster::Figure::height() const
{
    return m_height;
}

void diagramster::Figure::setHeight(const qreal &height)
{
    if (!qFuzzyCompare(m_height, height)) {
        m_height = height;
        emit heightChanged();
    }
}

qreal diagramster::Figure::width() const
{
    return m_width;
}

void diagramster::Figure::setWidth(const qreal &width)
{
    if (!qFuzzyCompare(m_width, width)) {
        m_width = width;
        emit widthChanged();
    }
}

qreal diagramster::Figure::y() const
{
    return m_y;
}

void diagramster::Figure::setY(const qreal &y)
{
    if (!qFuzzyCompare(m_y, y)) {
        m_y = y;
        emit yChanged();
    }
}

qreal diagramster::Figure::x() const
{
    return m_x;
}

void diagramster::Figure::setX(const qreal &x)
{
    if (!qFuzzyCompare(m_x, x)) {
        m_x = x;
        emit xChanged();
    }
}
