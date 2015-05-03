#include "contextobject.h"
#include "datacontext.h"

ContextObject::ContextObject(DataContext* context) : DataObject()
{
    this->set_id(QUuid::createUuid());

    if(context != NULL)
        this->addContext(*context);
}

ContextObject::~ContextObject()
{
    foreach(DataContext* context, this->_contexts)
        context->remove(this->id());
}

void ContextObject::addContext(DataContext& context)
{
    if(!this->_contexts.contains(&context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.append(&context);
        context.add(*this);
    }
}

void ContextObject::removeContext(DataContext& context)
{
    if(this->_contexts.contains(&context))
    {
        QMutexLocker(&this->mutex);
        this->_contexts.removeOne(&context);
        context.remove(this->id());
    }
}

bool ContextObject::equals(DataObject& obj) const
{
    auto metaObject1 = this->metaObject();
    auto metaObject2 = obj.metaObject();

    if(metaObject1->className() == metaObject2->className())
    {
        auto equals = true;

        for(auto i = 2; i < metaObject1->propertyCount(); i++)
        {
            QString tName(metaObject1->property(i).typeName());
            auto pName = metaObject1->property(i).name();

            if(tName.endsWith("*"))
            {
                DataObject* tObj = this->property(pName).value<DataObject*>();
                DataObject* oObj = obj.property(pName).value<DataObject*>();

                if(tObj != NULL && oObj != NULL)
                {
                    equals = tObj->equals(*oObj);
                }
                else if((tObj != NULL && oObj == NULL) || (tObj == NULL && oObj != NULL))
                {
                    equals = false;
                }
            }
            else if(tName.startsWith("QList"))
            {
                auto tIterable = this->property(pName).value<QSequentialIterable>();
                auto oIterable = obj.property(pName).value<QSequentialIterable>();

                foreach(const QVariant& tItem, tIterable)
                {
                    auto tfObj = tItem.value<DataObject*>();
                    auto found = false;

                    foreach(const QVariant& oItem, oIterable)
                    {
                        auto ofObj = oItem.value<DataObject*>();

                        found = tfObj->equals(*ofObj); // TODO how to avoid a worst case crash at this point?

                        if(found)
                            break;
                    }

                    if(!found)
                    {
                        equals = false;
                        break;
                    }
                }
            }
            else
            {
                auto value1 = this->property(pName);
                auto value2 = obj.property(pName);
                equals = value1.toString() == value2.toString();
            }

            if(!equals) break;
        }

        return equals;
    }
    else return false;
}

void ContextObject::updateFrom(DataObject& obj)
{
    auto metaObject1 = this->metaObject();
    auto metaObject2 = obj.metaObject();

    if(metaObject1->className() == metaObject2->className())
    {
        for(auto i = 2; i < metaObject1->propertyCount(); i++)
        {
            auto pName = metaObject1->property(i).name();

            this->setProperty(pName, obj.property(pName));
        }
    }
    else throw(new TypeNotMatchingException());
}

