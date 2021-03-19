#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "basicobject.h"

namespace diagramster
{

class Diagram : public BasicObject
{
    Q_OBJECT

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)

public:
    Q_INVOKABLE explicit Diagram(const QString& name = QString(),
                                 QObject* parent = Q_NULLPTR,
                                 const QUuid &uid = QUuid());

    qreal width() const;
    void setWidth(const qreal &width);

    qreal height() const;
    void setHeight(const qreal &height);

signals:
    void widthChanged();
    void heightChanged();

private:
    qreal m_width = 0.0;
    qreal m_height = 0.0;
};

}



#endif // DIAGRAM_H
