#include "basicobject.h"
#include <QChildEvent>
#include <QDebug>
#include <QMetaProperty>

diagramster::BasicObject::BasicObject(const QString &name, QObject *parent, const QUuid& uid)
    : QObject(), m_uid(uid.isNull() ? QUuid::createUuid() : uid)
{
    setObjectName(name);

    // If the parent is set with constructor (QObject(parent)),
    // the child (this) is not enough constructed for correct
    // BasicObject::childEvent() call
    setParent(parent);
}

diagramster::BasicObject::~BasicObject()
{

}

void diagramster::BasicObject::appendChild(QObject *object)
{
    if (!object) return;
    if (object->parent() == this) return;

    object->setParent(this);
}

void diagramster::BasicObject::removeChild(QObject *object)
{
    if (!object) return;
    if (object->parent() != this) return;

    object->setParent(nullptr);
}

void diagramster::BasicObject::clearChildren()
{
    for (auto child : children())
        removeChild(child);
}

int diagramster::BasicObject::childrenCount() const
{
    return children().size();
}

QList<diagramster::BasicObject *> diagramster::BasicObject::basicObjectChildren() const
{
    return m_basicObjectChildrenList;
}

int diagramster::BasicObject::basicObjectChildrenCount() const
{
    return m_basicObjectChildrenList.size();
}

diagramster::BasicObject *diagramster::BasicObject::findBasicObjectChild(const QUuid &uid, Qt::FindChildOptions options) const
{
    if (auto basicObject = m_basicObjectChildrenUIDHash.value(uid, nullptr))
        return basicObject;

    if (options == Qt::FindChildrenRecursively)
    {
        for (auto child : basicObjectChildren())
            if (auto obj = child->findBasicObjectChild(uid, options))
                return obj;
    }

    return nullptr;
}

void diagramster::BasicObject::insertBasicObjectChild(int index, diagramster::BasicObject *child)
{
    if (index >= 0 && index < m_basicObjectChildrenList.size()) {
        appendBasicObjectChild(child);
        moveBasicObjectChild(m_basicObjectChildrenList.size()-1, index);
    }
}

void diagramster::BasicObject::appendBasicObjectChild(diagramster::BasicObject  *child)
{
    appendChild(child);
}

void diagramster::BasicObject::prependBasicObjectChild(diagramster::BasicObject *child)
{
    insertBasicObjectChild(0, child);
}

void diagramster::BasicObject::moveBasicObjectChild(int from, int to)
{
    if ((from >= 0 && from < m_basicObjectChildrenList.size()) && (to >= 0 && to < m_basicObjectChildrenList.size()))
        m_basicObjectChildrenList.move(from, to);
}

void diagramster::BasicObject::moveBasicObjectChild(diagramster::BasicObject *child, int to)
{
    moveBasicObjectChild(m_basicObjectChildrenList.indexOf(child), to);
}

void diagramster::BasicObject::clearBasicObjectChildren()
{
    for (auto child : m_basicObjectChildrenList)
        removeChild(child);
}

void diagramster::BasicObject::childEvent(QChildEvent *event)
{
    QObject::childEvent(event);

    if (!(event->child())) {
        qWarning() << "BasicObject::childEvent() : !event->child()";
        return;
    }

    auto basicObjChild = qobject_cast<BasicObject*>(event->child());
    if (!basicObjChild) return;

    if (event->added()) {
        m_basicObjectChildrenList.append(basicObjChild);
        m_basicObjectChildrenUIDHash.insert(basicObjChild->uid(), basicObjChild);
        emit childAdded(basicObjChild);
    }

    if (event->removed()) {
        m_basicObjectChildrenList.removeOne(basicObjChild);
        m_basicObjectChildrenUIDHash.remove(basicObjChild->uid());
        emit childRemoved(basicObjChild);
    }
}

QUuid diagramster::BasicObject::uid() const
{
    return m_uid;
}

bool diagramster::BasicObject::isEqualTo(const diagramster::BasicObject *object) const
{
    if (this == object)
        return true;

    if (!object)
        return false;

    if (typeid(*this) != typeid(*object))
        return false;

    auto thisMeta   = metaObject();
    auto objectMeta = object->metaObject();

    if (!thisMeta || !objectMeta) {
        qWarning() << "BasicObject::isEqualTo() : !metaObject";
        return false;
    }

    if (thisMeta->propertyCount() != objectMeta->propertyCount())
        return false;

    int count = objectMeta->propertyCount();

    for (int i = 0; i < count; ++i)
    {
        auto thisMetaProperty   = thisMeta->property(i);
        auto objectMetaProperty = objectMeta->property(i);

        if (!strcmp(thisMetaProperty.name(), BasicObject::UID_PROPERTY_NAME) ||
            !strcmp(objectMetaProperty.name(), BasicObject::UID_PROPERTY_NAME))
            continue;

        auto thisPropertyValue   = thisMetaProperty.read(this);
        auto objectPropertyValue = objectMetaProperty.read(object);

        if (!thisPropertyValue.isValid() || !objectPropertyValue.isValid()) {
            qWarning() << "BasicObject::isEqualTo() : (!thisPropertyValue.isValid() || !objectPropertyValue.isValid())";
            return false;
        }

        if (thisPropertyValue != objectPropertyValue)
            return false;
    }

    return true;
}

bool diagramster::BasicObject::isRecursivelyEqualTo(const diagramster::BasicObject *object) const
{
    if (this == object)
        return true;

    if (!isEqualTo(object))
        return false;

    auto childrenThis = basicObjectChildren();
    auto childrenObject = object->basicObjectChildren();

    if (childrenThis.size() != childrenObject.size())
        return false;

    for (int i = 0; i < childrenThis.size(); ++i)
        if (!(childrenThis[i]->isRecursivelyEqualTo(childrenObject[i])))
            return false;

    return true;
}




