#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QUuid>
#include "basicobject.h"

namespace diagramster
{

class BasicObjectMetaFactory
{
public:
    // Use it only after registerMetaTypes()
    static BasicObject* create(const QString& typeName,
                               const QString& objectName = QString(),
                               QObject *parent = Q_NULLPTR,
                               const QUuid& uid = QUuid());

    // You have to register all new Object-based classes here manually
    static void registerMetaTypes();
};

}

#endif // OBJECTFACTORY_H
