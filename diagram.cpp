#include "diagram.h"

diagramster::Diagram::Diagram(const QString &name, QObject *parent, const QUuid &uid)
    : BasicObject(name, parent, uid)
{

}

qreal diagramster::Diagram::height() const
{
    return m_height;
}

void diagramster::Diagram::setHeight(const qreal &height)
{
    if (!qFuzzyCompare(m_height, height)) {
        m_height = height;
        emit heightChanged();
    }
}

qreal diagramster::Diagram::width() const
{
    return m_width;
}

void diagramster::Diagram::setWidth(const qreal &width)
{
    if (!qFuzzyCompare(m_width, width)) {
        m_width = width;
        emit widthChanged();
    }
}
