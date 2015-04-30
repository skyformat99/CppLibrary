#include "datacontext.h"

DataContext::DataContext()
{
    this->_id = QUuid::createUuid();
    DataContextManager::instance()->add(this);

    qDebug() << "datacontext" << this->_id << ": creating context";
}

DataContext::~DataContext()
{
    QMutexLocker(&this->mutex);

    DataContextManager::instance()->remove(this);

    // destroy dataobjects which are only contained in this context
    foreach(QUuid id, this->hash.keys())
    {
        this->remove(id);
    }
}

void DataContext::add(DataObject *obj)
{
    if(!this->hash.contains(obj->id()))
    {
        QMutexLocker(&this->mutex);
        this->onAdd(obj);
    }
}

void DataContext::onAdd(DataObject *obj)
{
    qDebug() << "datacontext" << this->_id << ": adding data object" << obj->id();
    this->hash.insert(obj->id(), obj);
    obj->addContext(this);
}

void DataContext::remove(const QUuid &id)
{
    if(this->hash.contains(id))
    {
        QMutexLocker(&this->mutex);
        this->onRemove(id);
    }
}

void DataContext::onRemove(const QUuid &id)
{
    qDebug() << "datacontext" << this->_id << ": removing data object" << id;

    auto obj = this->hash.take(id);
    obj->removeContext(this);

    auto multipleContexts = false;
    foreach(DataContext *context, DataContextManager::instance()->getAll())
    {
        if(this != context && context->hash.contains(id))
        {
            multipleContexts = true;
            break;
        }
    }

    if(!multipleContexts)
    {
        delete obj;
    }
}

DataObject* DataContext::get(const QUuid &id)
{
    QMutexLocker(&this->mutex);
    return this->onGet(id);
}

DataObject* DataContext::onGet(const QUuid &id)
{
    return this->hash.value(id, 0);
}
