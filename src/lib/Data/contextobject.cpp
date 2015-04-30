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

bool ContextObject::equals(DataObject *obj) const
{
    auto metaObject1 = this->metaObject();
    auto metaObject2 = obj->metaObject();

    if(metaObject1->className() == metaObject2->className())
    {
        auto equals = true;

        for(auto i = 2; i < metaObject1->propertyCount(); i++)
        {
            QString tName(metaObject1->property(i).typeName());
            auto pName = metaObject1->property(i).name();

            if(tName.endsWith("*"))
            {
                auto tObj = this->property(pName).value<DataObject*>();
                auto oObj = obj->property(pName).value<DataObject*>();

                if(tObj != 0 && oObj != 0)
                {
                    equals = tObj->equals(oObj);
                }
                else if((tObj != 0 && oObj == 0) || (tObj == 0 && oObj != 0))
                {
                    equals = false;
                }
            }
            else
            {
                auto value1 = this->property(pName);
                auto value2 = obj->property(pName);
                equals = value1.toString() == value2.toString();
            }

            if(!equals) break;
        }

        return equals;
    }
    else return false;
}

void ContextObject::updateFrom(DataObject *obj)
{
    auto metaObject1 = this->metaObject();
    auto metaObject2 = obj->metaObject();

    if(metaObject1->className() == metaObject2->className())
    {
        for(auto i = 2; i < metaObject1->propertyCount(); i++)
        {
            auto pName = metaObject1->property(i).name();

            this->setProperty(pName, obj->property(pName));
        }
    }
    else throw(new TypeNotMatchingException());
}

