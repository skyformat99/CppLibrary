#include "storagecontext.h"

StorageContext::StorageContext() : DataContext()
{

}

StorageContext::~StorageContext()
{

}

void StorageContext::save(const QUuid& id)
{
    if(this->hash.contains(id))
    {
        QMutexLocker(&this->mutex);
        this->onSave(id);
    }
    else throw(new ObjectNotFoundInDataContextException(id));
}

void StorageContext::saveAll()
{
    QMutexLocker(&this->mutex);
    this->onSaveAll();
}

void StorageContext::update(const QUuid& id)
{
    if(this->hash.contains(id))
    {
        QMutexLocker(&this->mutex);
        this->onUpdate(id);
    }
    else throw(new ObjectNotFoundInDataContextException(id));
}

void StorageContext::updateAll()
{
    QMutexLocker(&this->mutex);
    this->onUpdateAll();
}
