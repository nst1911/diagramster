#include "connectionline.h"

diagramster::ConnectionLine::ConnectionLine(const QString &name, QObject *parent, const QUuid &uid)
    : Figure(name, parent, uid)
{

}

diagramster::Block::Connector *diagramster::ConnectionLine::startConnector() const
{
    return m_startConnector;
}

void diagramster::ConnectionLine::setStartConnector(diagramster::Block::Connector *startConnector)
{
    if (m_startConnector != startConnector) {
        m_startConnector = startConnector;
        emit startConnectorChanged();
    }
}

diagramster::Block::Connector *diagramster::ConnectionLine::endConnector() const
{
    return m_endConnector;
}

void diagramster::ConnectionLine::setEndConnector(diagramster::Block::Connector *endConnector)
{
    if (m_endConnector != endConnector) {
        m_endConnector = endConnector;
        emit endConnectorChanged();
    }
}

QString diagramster::ConnectionLine::startConnectorString() const
{
    return Block::Connector::toString(startConnector());
}

void diagramster::ConnectionLine::setStartConnectorString(const QString &str)
{
    // ...
}

QString diagramster::ConnectionLine::endConnectorString() const
{
    return Block::Connector::toString(endConnector());
}

void diagramster::ConnectionLine::setEndConnectorString(const QString &str)
{
    // ...
}

int diagramster::ConnectionLine::lineWidth() const
{
    return m_lineWidth;
}

void diagramster::ConnectionLine::setLineWidth(int lineWidth)
{
    if (m_lineWidth != lineWidth) {
        m_lineWidth = lineWidth;
        emit lineWidthChanged();
    }
}

QColor diagramster::ConnectionLine::lineColor() const
{
    return m_lineColor;
}

void diagramster::ConnectionLine::setLineColor(const QColor &lineColor)
{
    if (m_lineColor != lineColor) {
        m_lineColor = lineColor;
        emit lineWidthChanged();
    }
}


