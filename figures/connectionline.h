#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

#include "figure.h"
#include "block.h"

namespace diagramster
{

class ConnectionLine : public Figure
{
    Q_OBJECT

    Q_PROPERTY(QUuid startBlockUid READ startBlockUid WRITE setStartBlockUid NOTIFY startBlockChanged STORED false)
    Q_PROPERTY(QUuid endBlockUid READ endBlockUid WRITE setEndBlockUid NOTIFY endBlockChanged STORED false)

    Q_PROPERTY(int startBlockConnectorId READ startBlockConnectorId WRITE setStartBlockConnectorId NOTIFY startBlockConnectorIdChanged STORED false)
    Q_PROPERTY(int endBlockConnectorId READ endBlockConnectorId WRITE setEndBlockConnectorId NOTIFY endBlockConnectorIdChanged STORED false)

    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)

public:
    Q_INVOKABLE explicit ConnectionLine(const QString& name = QString(),
                                        QObject* parent = Q_NULLPTR,
                                        const QUuid& uid = QUuid());

    Block *startBlock() const;
    void setStartBlock(Block *startBlock);
    void setStartBlock(Block *startBlock, int connectorId);

    Block *endBlock() const;
    void setEndBlock(Block *endBlock);
    void setEndBlock(Block *endBlock, int connectorId);

    // setStartBlockUid(), setEndBlockUid() look up the block with UID only
    // among ConnectionLine's siblings and their children recursively

    QUuid startBlockUid() const;
    void setStartBlockUid(const QUuid& uid);

    QUuid endBlockUid() const;
    void setEndBlockUid(const QUuid& uid);

    int startBlockConnectorId() const;
    void setStartBlockConnectorId(int startBlockConnectorId);

    int endBlockConnectorId() const;
    void setEndBlockConnectorId(int endBlockConnectorId);

    Block::Connector* startBlockConnector() const;
    Block::Connector* endBlockConnector() const;

    int lineWidth() const;
    void setLineWidth(int lineWidth);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

    bool isValid() const;

signals:
    void startBlockChanged();
    void endBlockChanged();
    void startBlockConnectorIdChanged();
    void endBlockConnectorIdChanged();
    void lineWidthChanged();
    void lineColorChanged();

protected:
    Block* getBlockWithUid(const QUuid& uid) const;

private:
    Block* m_startBlock = nullptr;
    Block* m_endBlock = nullptr;

    int m_startBlockConnectorId = -1;
    int m_endBlockConnectorId   = -1;

    int m_lineWidth = 1;
    QColor m_lineColor = QColor("black");
};

}

#endif // CONNECTIONLINE_H
