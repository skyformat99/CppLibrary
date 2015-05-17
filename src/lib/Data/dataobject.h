#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QtCore>
#include <QSharedPointer>
#include "dataexceptions.h"
#include "dataobjectfactory.h"

// macro that autoexecutes constructor registration
#define DATAOBJECT_REGISTER(name) \
    class regHelper##name { public: regHelper##name() { name::reg(); } ~regHelper##name(){}}; \
    regHelper##name regHelper##name##_; \
    Q_DECLARE_METATYPE(QSharedPointer<name>) \
    Q_DECLARE_METATYPE(name*) \
    Q_DECLARE_METATYPE(QList<QSharedPointer<name>>) \
    Q_DECLARE_METATYPE(QList<name*>)

// macro does the constructor registration
#define DATAOBJECT(name) \
    public: \
        static void reg() { DataObjectFactory::typeMap[#name] = &createDataObjectInstance<name>; }

// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for subobjects types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
// also it supports lazy loading through the name##Loading signal
#define REF_PROPERTY(type, name) \
    Q_SIGNAL void name##Changed(); \
    Q_SIGNAL void name##Loading(); \
    private: \
        QSharedPointer<type> _##name; \
        bool _##name##Loaded = false; \
        mutable QMutex _mutex_##name; \
    public: \
        QSharedPointer<type> name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        DataObject* __g_##name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return (DataObject*)this->_##name.data(); \
        } \
        Q_SLOT void set_##name(QSharedPointer<type> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            if(value != this->_##name) \
            { \
                emit propertyChanging(#name); \
                this->_##name = value; \
                emit propertyChanged(#name); \
                emit name##Changed(); \
            } \
        } \
        Q_SLOT void __g_set_##name(DataObject* value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            if(value != this->_##name) \
            { \
                emit propertyChanging(#name); \
                this->_##name = QSharedPointer<type>((type*)value); \
                emit propertyChanged(#name); \
                emit name##Changed(); \
            } \
        } \
    Q_PROPERTY(QSharedPointer<type> name READ name WRITE set_##name NOTIFY name##Changed) \
    Q_PROPERTY(DataObject* __g_##name READ __g_##name WRITE __g_set_##name NOTIFY name##Changed)

// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for value types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
#define VAL_PROPERTY(type, name, def) \
    Q_SIGNAL void name##Changed(); \
    private: \
        type _##name = def; \
        mutable QMutex _mutex_##name; \
    public: \
        type name() \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        \
        Q_SLOT void set_##name(type value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            if(value != this->_##name) \
            { \
                emit propertyChanging(#name); \
                this->_##name = value; \
                emit propertyChanged(#name); \
                emit name##Changed(); \
            } \
        } \
    Q_PROPERTY(type name READ name WRITE set_##name NOTIFY name##Changed)

// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for subobjects types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
// also it supports lazy loading through the name##Loading signal
#define NREF_PROPERTY(type, name) \
    Q_SIGNAL void name##Changed(); \
    Q_SIGNAL void name##Loading(); \
    private: \
        QList<QSharedPointer<type>> _##name; \
        bool _##name##Loaded = false; \
        mutable QMutex _mutex_##name; \
    public: \
        QList<QSharedPointer<type>> name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        QList<DataObject*> __g_##name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            \
            QList<DataObject*> list; \
            foreach(QSharedPointer<type> var, this->_##name) list.append((DataObject*)var.data()); \
            return list; \
        } \
        Q_SLOT void set_##name(QList<QSharedPointer<type>> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            emit propertyChanging(#name); \
            this->_##name = value; \
            emit propertyChanged(#name); \
            emit name##Changed(); \
        } \
        Q_SLOT void __g_set_##name(QList<DataObject*> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            emit propertyChanging(#name); \
            this->_##name.clear(); \
            foreach(DataObject* var, value) this->_##name.append(QSharedPointer<type>((type*)var)); \
            emit propertyChanged(#name); \
            emit name##Changed(); \
        } \
    Q_PROPERTY(QList<QSharedPointer<type>> name READ name WRITE set_##name NOTIFY name##Changed) \
    Q_PROPERTY(QList<DataObject*> __g_##name READ __g_##name WRITE __g_set_##name NOTIFY name##Changed)

// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for subobjects types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
// also it supports lazy loading through the name##Loading signal
#define NVAL_PROPERTY(type, name) \
    Q_SIGNAL void name##Changed(); \
    Q_SIGNAL void name##Loading(); \
    private: \
        QList<type> _##name; \
        bool _##name##Loaded = false; \
        mutable QMutex _mutex_##name; \
    public: \
        QList<type> name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        QList<QVariant> __g_##name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            \
            QList<QVariant> list; \
            foreach(type var, this->_##name) list.append(QVariant(var)); \
            return list; \
        } \
        Q_SLOT void set_##name(QList<type> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            emit propertyChanging(#name); \
            this->_##name = value; \
            emit propertyChanged(#name); \
            emit name##Changed(); \
        } \
        Q_SLOT void __g_set_##name(QList<QVariant> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            emit propertyChanging(#name); \
            this->_##name.clear(); \
            foreach(QVariant var, value) this->_##name.append(var.value<type>()); \
            emit propertyChanged(#name); \
            emit name##Changed(); \
        } \
    Q_PROPERTY(QList<type> name READ name WRITE set_##name NOTIFY name##Changed) \
    Q_PROPERTY(QList<QVariant> __g_##name READ __g_##name WRITE __g_set_##name NOTIFY name##Changed)

class DataObject : public QObject
{
    Q_OBJECT
public:
    DataObject();
    ~DataObject();

    virtual bool equals(DataObject& obj) const;
    virtual void updateFrom(DataObject& obj);
    QSharedPointer<DataObject> clone();

protected:
    mutable QMutex mutex;

signals:
    // properties are implementing the PropertyChanging and PropertyChanged pattern known from .NET aside of the Changed pattern from Qt which you should prefer
    void propertyChanging(const QString& propertyName);
    void propertyChanged(const QString& propertyName);
};

Q_DECLARE_METATYPE(QSharedPointer<DataObject>)
Q_DECLARE_METATYPE(DataObject*)
Q_DECLARE_METATYPE(QList<QSharedPointer<DataObject>>)
Q_DECLARE_METATYPE(QList<DataObject*>)

#endif // DATAOBJECT_H

