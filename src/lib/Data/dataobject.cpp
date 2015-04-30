#include "dataobject.h"
#include "datacontext.h"

DataObject::DataObject(DataContext* context) : QObject(0)
{
    this->set_id(QUuid::createUuid());

    this->addContext(context);
}

DataObject::~DataObject()
{
    foreach(DataContext *context, this->_contexts)
        context->remove(this->id());
}

bool DataObject::equals(DataObject *obj) const
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

void DataObject::updateFrom(DataObject *obj)
{
    auto metaObject1 = this->metaObject();
    auto metaObject2 = obj->metaObject();

    if(metaObject1->className() == metaObject2->className())
    {
        if(this->property("id") == obj->property("id"))
        {
            for(auto i = 2; i < metaObject1->propertyCount(); i++)
            {
                auto pName = metaObject1->property(i).name();

                this->setProperty(pName, obj->property(pName));
            }
        }
        else throw(new IdNotMatchingException());
    }
    else throw(new TypeNotMatchingException());
}

void DataObject::addContext(DataContext *context)
{
    if(!this->_contexts.contains(context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.append(context);
        context->add(this);
    }
}

void DataObject::removeContext(DataContext *context)
{
    if(this->_contexts.contains(context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.removeOne(context);
        context->remove(this->id());
    }
}

