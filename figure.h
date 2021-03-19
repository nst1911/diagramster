#ifndef OBJECT_H
#define OBJECT_H

#include "basicobject.h"
#include <QPointF>
#include <QSizeF>

namespace diagramster
{

class Figure : public BasicObject
{
    Q_OBJECT

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY xChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    Q_INVOKABLE explicit Figure(const QString& name = QString(),
                                QObject* parent = Q_NULLPTR,
                                const QUuid &uid = QUuid());

    virtual ~Figure() {}

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

signals:
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void visibleChanged();

private:
    qreal m_x = 0.0;
    qreal m_y = 0.0;
    qreal m_width = 0.0;
    qreal m_height = 0.0;
    bool m_visible = true;
};

}

#endif // OBJECT_H
