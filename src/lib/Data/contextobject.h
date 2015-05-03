#ifndef CONTEXTOBJECT_H
#define CONTEXTOBJECT_H

#include "dataobject.h"
#include "contextobjectfactory.h"

class DataContext;

// macro that autoexecutes constructor registration
#define CONTEXTOBJECT_REGISTER(name) \
    class regHelper##name { public: regHelper##name() { name::reg(); } ~regHelper##name(){}}; \
    regHelper##name regHelper##name##_;

// macro does the constructor registration
#define CONTEXTOBJECT(name) \
    public: \
        static void reg() { ContextObjectFactory::typeMap[#name] = &createContextObjectInstance<name>; }

class ContextObject : public DataObject
{
    Q_OBJECT
    VALUE_PROPERTY(QUuid, id, QUuid())    // each contextobject has an unique identifier

public:
    ContextObject(DataContext* context);
    ~ContextObject();

    void addContext(DataContext& context);
    void removeContext(DataContext& context);

    virtual bool equals(DataObject& obj) const override;
    virtual void updateFrom(DataObject& obj) override;

private:
    QList<DataContext*> _contexts;
};

#endif // CONTEXTOBJECT_H
