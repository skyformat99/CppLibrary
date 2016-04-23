#include "dataobject.h"

namespace ralph {
    namespace data {

        DataObject::DataObject() : QObject(0)
        {
        }

        DataObject::~DataObject()
        {
        }

        bool DataObject::equals(DataObject &obj) const
        {
            const QMetaObject* metaObject1 = this->metaObject();
            const QMetaObject* metaObject2 = obj.metaObject();

            if(metaObject1->className() == metaObject2->className())
            {
                bool equals = true;

                for(int i = 1; i < metaObject1->propertyCount(); i++)
                {
                    QString tName(metaObject1->property(i).typeName());
                    QString pName = metaObject1->property(i).name();

                    if(tName.startsWith("QSharedPointer<"))
                    {
                        QSharedPointer<DataObject> tObj = this->property(pName.toStdString().c_str()).value<QSharedPointer<DataObject>>();
                        QSharedPointer<DataObject> oObj = obj.property(pName.toStdString().c_str()).value<QSharedPointer<DataObject>>();

                        if(tObj != NULL && oObj != NULL)
                        {
                            equals = tObj->equals(*oObj);
                        }
                        else if((tObj != NULL && oObj == NULL) || (tObj == NULL && oObj != NULL))
                        {
                            equals = false;
                        }
                    }
                    else if(tName.startsWith("QList<"))
                    {
                        QSequentialIterable tIterable = this->property(pName.toStdString().c_str()).value<QSequentialIterable>();
                        QSequentialIterable oIterable = obj.property(pName.toStdString().c_str()).value<QSequentialIterable>();

                        foreach(const QVariant &tItem, tIterable)
                        {
                            QSharedPointer<DataObject> tfObj = tItem.value<QSharedPointer<DataObject>>();
                            bool found = false;

                            foreach(const QVariant &oItem, oIterable)
                            {
                                QSharedPointer<DataObject> ofObj = oItem.value<QSharedPointer<DataObject>>();

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
                        QVariant value1 = this->property(pName.toStdString().c_str());
                        QVariant value2 = obj.property(pName.toStdString().c_str());
                        equals = value1.toString() == value2.toString();
                    }

                    if(!equals) break;
                }

                return equals;
            }
            else return false;
        }

        void DataObject::updateFrom(DataObject &obj)
        {
            const QMetaObject* metaObject1 = this->metaObject();
            const QMetaObject* metaObject2 = obj.metaObject();

            if(metaObject1->className() == metaObject2->className())
            {
                for(int i = 1; i < metaObject1->propertyCount(); i++)
                {
                    QString pName = metaObject1->property(i).name();

                    this->setProperty(pName.toStdString().c_str(), obj.property(pName.toStdString().c_str()));
                }
            }
            else throw(new TypeNotMatchingException());
        }

        QSharedPointer<DataObject> DataObject::clone()
        {
            const QMetaObject* metaObject = this->metaObject();
            QSharedPointer<DataObject> obj(DataObjectFactory::create(metaObject->className()));

            obj->updateFrom(*this);

            return obj;
        }

    }
}

