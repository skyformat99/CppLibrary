#ifndef STORAGECONTEXT_H
#define STORAGECONTEXT_H

#include <QtCore>
#include "datacontext.h"

class StorageContext : public DataContext
{
public:
    StorageContext();
    ~StorageContext();

    void save(const QUuid &id);
    void saveAll();
    void update(const QUuid &id);
    void updateAll();

protected:
    virtual void onSave(const QUuid &id) = 0;
    virtual void onSaveAll() = 0;
    virtual void onUpdate(const QUuid &id) = 0;
    virtual void onUpdateAll() = 0;
};

#endif // STORAGECONTEXT_H
