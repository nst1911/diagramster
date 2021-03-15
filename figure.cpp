#include "figure.h"
#include <QChildEvent>
#include <QXmlStreamWriter>

diagramster::Figure::Figure(const QString &name, QObject *parent, const QUuid& uid)
    : BasicObject(name, parent, uid)
{

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
