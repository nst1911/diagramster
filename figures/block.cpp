#include "block.h"
#include <QDebug>
#include <QMetaEnum>

diagramster::Block::Block(const QString &name, QObject *parent, const QUuid &uid)
    : Figure(name, parent, uid)
{

}

diagramster::Block::~Block()
{
    clearConnectors();
}

diagramster::Block::Connector *diagramster::Block::connector(int id)
{
    return m_connectorMap.value(id, nullptr);
}

QList<diagramster::Block::Connector *> diagramster::Block::connectors() const
{
    return m_connectorMap.values();
}

int diagramster::Block::connectorCount() const
{
    return m_connectorMap.size();
}

QStringList diagramster::Block::connectorList() const
{
    QStringList stringList;

    auto connectorList = connectors();

    for (auto c : connectorList)
        stringList.append(Connector::toString(c));

    return stringList;
}

void diagramster::Block::setConnectorList(const QStringList &list)
{
    for (auto connectorStr : list)
        addConnector(connectorStr);
}

void diagramster::Block::addConnector(QString str)
{
    if (auto connectorFromStr = Connector::fromString(str, this))
        m_connectorMap.insert(connectorFromStr->id(), connectorFromStr);
}

void diagramster::Block::addConnector(diagramster::Block::Side side, double relativePos)
{
    auto id = connectorCount();
    m_connectorMap.insert(id, new Connector(this, side, relativePos, id));
}

void diagramster::Block::removeConnector(int id)
{
    if (auto c = connector(id)) {
        m_connectorMap.remove(id);
        delete c;
    }
}

void diagramster::Block::clearConnectors()
{
    for (auto c : m_connectorMap.values())
        delete c;

    m_connectorMap.clear();
}

void diagramster::Block::fillSideWithConnectors(diagramster::Block::Side side, int count)
{
    if (count == 1) {
        addConnector(side, 0.5);
        return;
    }

    for (int i = 0; i < count; ++i)
        addConnector(side, double(i)/(count-1));

}

int diagramster::Block::strokeWidth() const
{
    return m_strokeWidth;
}

void diagramster::Block::setStrokeWidth(int strokeWidth)
{
    if (m_strokeWidth != strokeWidth) {
        m_strokeWidth = strokeWidth;
        emit strokeWidthChanged();
    }
}

QColor diagramster::Block::strokeColor() const
{
    return m_strokeColor;
}

void diagramster::Block::setStrokeColor(const QColor &color)
{
    if (m_strokeColor != color) {
        m_strokeColor = color;
        emit strokeColorChanged();
    }
}

diagramster::Block::Connector::Connector(diagramster::Block *block, diagramster::Block::Side side, double relativePos, int id)
    : m_block(block), m_side(side), m_relativePos(relativePos), m_id(id)
{

}

QPointF diagramster::Block::Connector::globalPos() const
{
    QPointF pos;

    switch (m_side)
    {
        case Left:
            pos.setX(m_block->x() + m_block->strokeWidth()/2);
            pos.setY(m_block->y() + m_block->height() * m_relativePos - m_block->strokeWidth()/2);
            break;
        case Right:
            pos.setX(m_block->x() + m_block->width() - m_block->strokeWidth()/2);
            pos.setY(m_block->y() + m_block->height() * m_relativePos - m_block->strokeWidth()/2);
            break;
        case Top:
            pos.setX(m_block->x() + m_block->width() * m_relativePos - m_block->strokeWidth()/2);
            pos.setY(m_block->y() + m_block->strokeWidth()/2);
            break;
        case Bottom:
            pos.setX(m_block->x() + m_block->width() * m_relativePos - m_block->strokeWidth()/2);
            pos.setY(m_block->y() + m_block->height() - m_block->strokeWidth()/2);
            break;
    }

    return pos;
}

diagramster::Block *diagramster::Block::Connector::block() const
{
    return m_block;
}

diagramster::Block::Side diagramster::Block::Connector::side() const
{
    return m_side;
}

void diagramster::Block::Connector::setSide(const diagramster::Block::Side &side)
{
    if (m_side != side)
        m_side = side;
}

double diagramster::Block::Connector::relativePos() const
{
    return m_relativePos;
}

void diagramster::Block::Connector::setRelativePos(double relativePos)
{
    if (!qFuzzyCompare(m_relativePos, relativePos))
        m_relativePos = relativePos;
}

int diagramster::Block::Connector::id() const
{
    return m_id;
}

QString diagramster::Block::Connector::toString(diagramster::Block::Connector *connector)
{
    return QString("%1 %2 %3 %4")
            .arg(connector->block()->uid().toString())
            .arg(connector->id())
            .arg(connector->relativePos())
            .arg(QMetaEnum::fromType<Block::Side>().valueToKey(connector->side()));
}

diagramster::Block::Connector *diagramster::Block::Connector::fromString(const QString &string, Block *block)
{
    Block::Side side;
    double relativePos;
    int id;
    QUuid blockUid;

    auto parseResult = parseString(string, &side, &relativePos, &id, &blockUid);
    if (!parseResult) return nullptr;

    return (blockUid == block->uid()) ? new Connector(block, side, relativePos, id) : nullptr;
}

bool diagramster::Block::Connector::parseString(const QString &string, Block::Side* side, double* relativePos, int *id, QUuid* blockUid)
{
    if (string.isEmpty())
        return false;

    QStringList splitted = string.split(" ");

    if (splitted.size() < 4)
        return false;

    (*blockUid)     = splitted.at(0);
    (*id)           = splitted.at(1).toInt();
    (*relativePos)  = splitted.at(2).toDouble();
    (*side)         = Block::Side(QMetaEnum::fromType<Block::Side>().keyToValue(splitted.at(3).toUtf8().constData()));

    return true;
}
