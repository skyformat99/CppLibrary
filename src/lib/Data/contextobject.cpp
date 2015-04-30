#include "contextobject.h"
#include "datacontext.h"

ContextObject::ContextObject(DataContext *context) : DataObject()
{
    this->set_id(QUuid::createUuid());

    this->addContext(context);
}

ContextObject::~ContextObject()
{
    foreach(DataContext *context, this->_contexts)
        context->remove(this->id());
}

void ContextObject::addContext(DataContext *context)
{
    if(!this->_contexts.contains(context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.append(context);
        context->add(this);
    }
}

void ContextObject::removeContext(DataContext *context)
{
    if(this->_contexts.contains(context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.removeOne(context);
        context->remove(this->id());
    }
}

