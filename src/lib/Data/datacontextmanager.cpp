#include "datacontextmanager.h"
#include "datacontext.h"

DataContextManager::DataContextManager()
{
}

DataContextManager::~DataContextManager()
{
}

DataContextManager DataContextManager::s_instance;
DataContextManager* DataContextManager::instance()
{
    return &DataContextManager::s_instance;
}

void DataContextManager::add(DataContext *context)
{
    QMutexLocker(&this->_mutex);
    this->_contexts.append(context);
}

void DataContextManager::remove(DataContext *context)
{
    QMutexLocker(&this->_mutex);
    this->_contexts.removeOne(context);
}

QList<DataContext*> DataContextManager::getAll() const
{
    return this->_contexts;
}

