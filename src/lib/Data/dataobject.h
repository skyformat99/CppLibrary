#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QtCore>
#include "dataexceptions.h"
#include "dataobjectfactory.h"

class DataContext;

// macro that autoexecutes constructor registration
#define DATAOBJECT_REGISTER(name) \
    class regHelper##name { public: regHelper##name() { name::reg(); } ~regHelper##name(){}}; \
    regHelper##name regHelper##name##_;

// macro does the constructor registration
#define DATAOBJECT(name) \
    public: \
        static void reg() { DataObjectFactory::typeMap[#name] = &createDataObjectInstance<name>; }

// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for value types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
#define VALUE_PROPERTY(type, name, def) \
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
#define OBJECT_PROPERTY(type, name) \
    Q_SIGNAL void name##Changed(); \
    Q_SIGNAL void name##Loading(); \
    private: \
        type *_##name = 0; \
        bool _##name##Loaded = false; \
        mutable QMutex _mutex_##name; \
    public: \
        type *name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        \
        Q_SLOT void set_##name(type *value) \
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
    Q_PROPERTY(type* name READ name WRITE set_##name NOTIFY name##Changed)

// TODO: excahnge QList with something supporting lazy loading
// macro creates full fledged Q_PROPERTIES with signals and slots as they are required for subobjects types and threadsafe working
// each property has its own lock, but the object can be locked as whole, so there's a check for this object mutex on each action the property takes
// also it supports lazy loading through the name##Loading signal
#define NOBJECTS_PROPERTY(type, name) \
    Q_SIGNAL void name##Changed(); \
    Q_SIGNAL void name##Loading(); \
    private: \
        QList<type*> _##name; \
        bool _##name##Loaded = false; \
        mutable QMutex _mutex_##name; \
    public: \
        QList<type*> name() \
        { \
            if(!this->_##name##Loaded) { emit name##Loading(); this->_##name##Loaded = true; } \
            \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            return this->_##name; \
        } \
        Q_SLOT void set_##name(QList<type*> value) \
        { \
            this->mutex.lock(); this->mutex.unlock(); \
            QMutexLocker(&this->_mutex_##name); \
            emit propertyChanging(#name); \
            this->_##name = value; \
            emit propertyChanged(#name); \
            emit name##Changed(); \
        } \
    Q_PROPERTY(QList<type*> name READ name WRITE set_##name NOTIFY name##Changed)

class DataObject : public QObject
{
    Q_OBJECT
    VALUE_PROPERTY(QUuid, id, QUuid())    // each object has an unique identifier
public:
    DataObject(DataContext *context);
    ~DataObject();

    bool equals(DataObject *obj) const;
    void updateFrom(DataObject *obj);
    void addContext(DataContext *context);
    void removeContext(DataContext * context);

protected:
    mutable QMutex mutex;

private:
    QList<DataContext*> _contexts;

signals:
    // properties are implementing the PropertyChanging and PropertyChanged pattern known from .NET aside of the Changed pattern from Qt which you should prefer
    void propertyChanging(const QString &propertyName);
    void propertyChanged(const QString &propertyName);
};

#endif // DATAOBJECT_H

