#ifndef BLOCK_H
#define BLOCK_H

#include "figure.h"
#include <QMap>
#include <QColor>

namespace diagramster
{

class Block : public Figure
{
    Q_OBJECT

    Q_PROPERTY(int strokeWidth READ strokeWidth WRITE setStrokeWidth NOTIFY strokeWidthChanged)
    Q_PROPERTY(QColor strokeColor READ strokeColor WRITE setStrokeColor NOTIFY strokeColorChanged)

    // TODO: NOTIFY signal?
    Q_PROPERTY(QStringList connectorList READ connectorList WRITE setConnectorList STORED false)

public:
    Q_INVOKABLE explicit Block(const QString& name = QString(),
                               QObject* parent = Q_NULLPTR,
                               const QUuid &uid = QUuid());
    virtual ~Block();

    enum Side {
        Left,
        Right,
        Top,
        Bottom
    };
    Q_ENUM(Side) // for converting enum->QString and vice versa

    class Connector; 

    Connector* connector(int id);
    QList<Connector*> connectors() const;
    int connectorCount() const;

    QStringList connectorList() const;
    void setConnectorList(const QStringList& list);

    void addConnector(QString str);
    void addConnector(Side side, double relativePos);
    void removeConnector(int id);
    void clearConnectors();

    void fillSideWithConnectors(Side side, int count);

    int strokeWidth() const;
    void setStrokeWidth(int strokeWidth);

    QColor strokeColor() const;
    void setStrokeColor(const QColor& color);

signals:
    void strokeWidthChanged();
    void strokeColorChanged();

private:
    QMap<int, Connector*> m_connectorMap;

    int    m_strokeWidth = 1;
    QColor m_strokeColor;
};

class Block::Connector
{
public:
    QPointF globalPos() const;

    Block *block() const;

    Block::Side side() const;
    void setSide(const Block::Side &side);

    double relativePos() const;
    void setRelativePos(double relativePos);

    int id() const;

    static QString toString(Connector* connector);

private:
    friend class Block;

    Connector(Block* block, Block::Side side, double relativePos, int id);

    static Connector* fromString(const QString& string, Block* block = nullptr);
    static bool parseString(const QString& string, diagramster::Block::Side *side, double *relativePos, int *id, QUuid *blockUid);

    Block* m_block;
    Block::Side m_side;
    double m_relativePos;
    int m_id;
};

}


#endif // BLOCK_H
