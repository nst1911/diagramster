#include "connectionline.h"
#include <QUuid>
#include <QDebug>

diagramster::ConnectionLine::ConnectionLine(const QString &name, QObject *parent, const QUuid &uid)
    : Figure(name, parent, uid)
{

}

diagramster::Block *diagramster::ConnectionLine::startBlock() const
{
    return m_startBlock;
}

void diagramster::ConnectionLine::setStartBlock(diagramster::Block *startBlock)
{
    if (m_startBlock != startBlock && startBlock != endBlock()) {
        m_startBlock = startBlock;
        emit startBlockChanged();
    }
}

void diagramster::ConnectionLine::setStartBlock(diagramster::Block *startBlock, int connectorId)
{
    setStartBlock(startBlock);
    setStartBlockConnectorId(connectorId);
}

QUuid diagramster::ConnectionLine::startBlockUid() const
{
    return startBlock() ? startBlock()->uid() : QUuid();
}

void diagramster::ConnectionLine::setStartBlockUid(const QUuid &uid)
{
    if (auto block = getBlockWithUid(uid))
        setStartBlock(block);
}

diagramster::Block *diagramster::ConnectionLine::endBlock() const
{
    return m_endBlock;
}

void diagramster::ConnectionLine::setEndBlock(diagramster::Block *endBlock)
{
    if (m_endBlock != endBlock && endBlock != startBlock())
    {
        m_endBlock = endBlock;
        emit endBlockChanged();
    }
}

void diagramster::ConnectionLine::setEndBlock(diagramster::Block *endBlock, int connectorId)
{
    setEndBlock(endBlock);
    setEndBlockConnectorId(connectorId);
}

QUuid diagramster::ConnectionLine::endBlockUid() const
{
    return endBlock() ? endBlock()->uid() : QUuid();
}

void diagramster::ConnectionLine::setEndBlockUid(const QUuid &uid)
{
    if (auto block = getBlockWithUid(uid))
        setEndBlock(block);
}

int diagramster::ConnectionLine::startBlockConnectorId() const
{
    return m_startBlockConnectorId;
}

void diagramster::ConnectionLine::setStartBlockConnectorId(int startBlockConnectorId)
{
    if (m_startBlockConnectorId != startBlockConnectorId)
    {
        m_startBlockConnectorId = startBlockConnectorId;
        emit startBlockConnectorIdChanged();
    }
}

int diagramster::ConnectionLine::endBlockConnectorId() const
{
    return m_endBlockConnectorId;
}

void diagramster::ConnectionLine::setEndBlockConnectorId(int endBlockConnectorId)
{
    if (m_endBlockConnectorId != endBlockConnectorId)
    {
        m_endBlockConnectorId = endBlockConnectorId;
        emit endBlockConnectorIdChanged();
    }
}

diagramster::Block::Connector *diagramster::ConnectionLine::startBlockConnector() const
{
    return startBlock() ? startBlock()->connector(startBlockConnectorId()) : nullptr;
}

diagramster::Block::Connector *diagramster::ConnectionLine::endBlockConnector() const
{
    return endBlock() ? endBlock()->connector(endBlockConnectorId()) : nullptr;
}

int diagramster::ConnectionLine::lineWidth() const
{
    return m_lineWidth;
}

void diagramster::ConnectionLine::setLineWidth(int lineWidth)
{
    if (m_lineWidth != lineWidth)
    {
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
    if (m_lineColor != lineColor)
    {
        m_lineColor = lineColor;
        emit lineColorChanged();
    }
}

bool diagramster::ConnectionLine::isValid() const
{
    if (!startBlock() || !endBlock())
        return false;

    if (!startBlockConnector() || !endBlockConnector())
        return false;

    return startBlock() != endBlock() && startBlockConnector() != endBlockConnector();
}

diagramster::Block *diagramster::ConnectionLine::getBlockWithUid(const QUuid &uid) const
{
    auto basicObjParent = dynamic_cast<BasicObject*>(parent());
    if (!basicObjParent) {
        qWarning() << "ConnectionLine::getBlockWithUid() : (!basicObjParent)";
        return nullptr;
    }

    auto block = dynamic_cast<Block*>(basicObjParent->findBasicObjectChild(uid));
    if (!block) qWarning() << "ConnectionLine::getBlockWithUid() : (!block)";

    return block;
}
