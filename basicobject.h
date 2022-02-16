#ifndef BASICOBJECT_H
#define BASICOBJECT_H

#include <QObject>
#include <QUuid>
#include <QList>
#include <QHash>

namespace diagramster
{

// BasicObject-based class use QObject tree as a tree structure (parents, children, ownership, etc)

// All BasicObject-based classes must:
// > have a Q_INVOKABLE constructor
// > have a virtual destructor
// > have a registered metatype (you can add registration code to BasicObjectFactory::registerMetaTypes() for convenience)

class BasicObject : public QObject
{
    Q_OBJECT

    // Data that have to be serialized/deserialized
    // must be declared as Q_PROPERTY and be convertable to QString

    // List properties have to be defined as QStringList

    Q_PROPERTY(QUuid uid READ uid)

public:
    // Bug: Object uniqueness problem - There can be several objects with the same UIDs
    // because UID can be passed as an argument of constructor

    Q_INVOKABLE explicit BasicObject(const QString& name = QString(),
                                     QObject* parent = Q_NULLPTR,
                                     const QUuid &uid = QUuid());
    virtual ~BasicObject();

    enum class ChildrenSort {
        Unsorted,
        OrderIndexSort
    };

    void appendChild(QObject* object);
    void removeChild(QObject* object);
    void clearChildren();
    int  childrenCount() const;

    QList<BasicObject*> basicObjectChildren() const;
    int basicObjectChildrenCount() const;

    BasicObject* findBasicObjectChild(const QUuid& uid, Qt::FindChildOptions options = Qt::FindChildrenRecursively) const;

    void insertBasicObjectChild(int index, BasicObject* child);
    void appendBasicObjectChild(BasicObject* child);
    void prependBasicObjectChild(BasicObject* child);

    void moveBasicObjectChild(int from, int to);
    void moveBasicObjectChild(BasicObject* child, int to);

    void clearBasicObjectChildren();

    QUuid uid() const;

    virtual bool isEqualTo(const BasicObject* object) const;
    bool isRecursivelyEqualTo(const BasicObject* object) const;

    constexpr static const char* OBJECT_NAME_PROPERTY_NAME = "objectName";
    constexpr static const char* UID_PROPERTY_NAME = "uid";

signals:
    void propertyDataChanged(const QString& propertyName);
    void childAdded(BasicObject* child);
    void childRemoved(BasicObject* child);
    void childMoved(BasicObject* child, int from, int to);

protected:
    virtual void childEvent(QChildEvent *event) override;

private:
    QUuid m_uid;

    QList<BasicObject*>        m_basicObjectChildrenList;
    QHash<QUuid, BasicObject*> m_basicObjectChildrenUIDHash;
};


}

#endif // BASICOBJECT_H
