#ifndef DATACONTEXT_H
#define DATACONTEXT_H

#include <QtCore>

#include "dataexceptions.h"
#include "dataobject.h"
#include "datacontextmanager.h"

class DataContext
{
public:
    DataContext();
    virtual ~DataContext();

    void add(DataObject* obj);
    void remove(const QUuid &id);
    DataObject* get(const QUuid &id);

protected:
    QHash<QUuid, DataObject*> hash;
    mutable QMutex mutex;

    virtual void onAdd(DataObject *obj);
    virtual void onRemove(const QUuid &id);
    virtual DataObject* onGet(const QUuid &id);

private:
    QUuid _id;  // we need this for now just for debugging reasons
};

#endif // DATACONTEXT_H
