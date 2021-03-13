#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

#include "figure.h"
#include "block.h"

namespace diagramster
{

class ConnectionLine : public Figure
{
    Q_OBJECT

    Q_PROPERTY(QString startConnector READ startConnectorString WRITE setStartConnectorString NOTIFY startConnectorChanged STORED false)
    Q_PROPERTY(QString endConnector READ endConnectorString WRITE setEndConnectorString NOTIFY endConnectorChanged STORED false)

    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)

public:
    Q_INVOKABLE explicit ConnectionLine(const QString& name = QString(),
                                        QObject* parent = Q_NULLPTR,
                                        const QUuid& uid = QUuid());

    Block::Connector *startConnector() const;
    void setStartConnector(Block::Connector *startConnector);

    Block::Connector *endConnector() const;
    void setEndConnector(Block::Connector *endConnector);

    QString startConnectorString() const;
    void setStartConnectorString(const QString& str);

    QString endConnectorString() const;
    void setEndConnectorString(const QString& str);

    int lineWidth() const;
    void setLineWidth(int lineWidth);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

signals:
    void startConnectorChanged();
    void endConnectorChanged();
    void lineWidthChanged();
    void lineColorChanged();

private:
    Block::Connector* m_startConnector = nullptr;
    Block::Connector* m_endConnector   = nullptr;

    int m_lineWidth = 1;
    QColor m_lineColor;
};

}

#endif // CONNECTIONLINE_H
