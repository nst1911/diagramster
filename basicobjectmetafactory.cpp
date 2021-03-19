#include <QDebug>
#include "basicobjectmetafactory.h"
#include "figures/block.h"
#include "figures/connectionline.h"
#include "diagram.h"

#define CREATE_WARNING_MSG(errorMsg) qWarning() << "BasicObjectFactory::create() for" << objectName << "of" << typeName << ":" << errorMsg

diagramster::BasicObject *diagramster::BasicObjectMetaFactory::create(const QString &typeName, const QString &objectName, QObject* parent, const QUuid &uid)
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

    auto obj = qobject_cast<BasicObject*>(metaObj->newInstance(Q_ARG(QString, objectName),
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

void diagramster::BasicObjectMetaFactory::registerMetaTypes()
{
    registerMetaType<BasicObject>();
    registerMetaType<Diagram>();
    registerMetaType<Figure>();
    registerMetaType<Block>();
    registerMetaType<ConnectionLine>();
}
