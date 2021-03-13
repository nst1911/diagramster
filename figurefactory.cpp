#include "figurefactory.h"
#include <QDebug>

#include "figures/block.h"
#include "figures/connectionline.h"

#define CREATE_WARNING_MSG(errorMsg) qWarning() << "FigureFactory::create() for" << figureName << "of" << typeName << ":" << errorMsg

diagramster::Figure *diagramster::FigureFactory::create(const QString &typeName, const QString &figureName, const QUuid &uid, QObject* parent)
{
    auto type = QMetaType::type(QString(typeName + "*").toLatin1());

    if (type == QMetaType::UnknownType) {
        CREATE_WARNING_MSG("type == QMetaType::UnknownType");
        return nullptr;
    }

    auto metaObj = QMetaType::metaObjectForType(type);

    if (!metaObj) {
        CREATE_WARNING_MSG("QMetaType::metaObjectForType(type) failed");
        return nullptr;
    }

    auto obj = qobject_cast<Figure*>(metaObj->newInstance(Q_ARG(QString, figureName),
                                                          Q_ARG(QObject*, parent),
                                                          Q_ARG(QUuid, uid)));

    if (!obj)
        CREATE_WARNING_MSG("There is no constructor with args (QString, QObject*, QUuid)");

    return obj;
}

template<typename T> void registerMetaType()
{
    QString className = T::staticMetaObject.className();
    className += "*";
    qRegisterMetaType<T*>(className.toUtf8().constData());
}

void diagramster::FigureFactory::registerMetaTypes()
{
    registerMetaType<Figure>();
    registerMetaType<Block>();
    registerMetaType<ConnectionLine>();
}
