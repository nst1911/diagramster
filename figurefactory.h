#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QUuid>
#include "figure.h"

namespace diagramster
{

class FigureFactory
{
public:
    // Use it only after registerMetaTypes()
    static Figure* create(const QString& typeName,
                          const QString& figureName = QString(),
                          const QUuid& uid = QUuid(),
                          QObject *parent = Q_NULLPTR);

    // You have to register all new Object-based classes here manually
    static void registerMetaTypes();
};

}

#endif // OBJECTFACTORY_H
