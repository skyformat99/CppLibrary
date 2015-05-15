#include "dataobjectfactory.h"

QMap<QString, DataObject* (*)()> DataObjectFactory::typeMap;
DataObject* DataObjectFactory::createInstance(const QString& s)
{
    if(DataObjectFactory::contains(s))
        return DataObjectFactory::typeMap[s]();
    else
        throw(new TypeNotRegisteredException());
}

bool DataObjectFactory::contains(const QString& s)
{
    return DataObjectFactory::typeMap.contains(s);
}
