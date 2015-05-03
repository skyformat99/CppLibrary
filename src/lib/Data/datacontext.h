#ifndef DATACONTEXT_H
#define DATACONTEXT_H

#include <QtCore>

#include "dataexceptions.h"
#include "contextobject.h"
#include "datacontextmanager.h"

class DataContext
{
public:
    DataContext();
    virtual ~DataContext();

    void add(ContextObject& obj);
    void remove(const QUuid& id);
    ContextObject* get(const QUuid& id);

protected:
    QHash<QUuid, ContextObject*> hash;
    mutable QMutex mutex;

    virtual void onAdd(ContextObject& obj);
    virtual void onRemove(const QUuid& id);
    virtual ContextObject* onGet(const QUuid& id);

private:
    QUuid _id;  // we need this for now just for debugging reasons
};

#endif // DATACONTEXT_H
