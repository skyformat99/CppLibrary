#include "dataobjectfactory.h"
#include "contextobjectfactory.h"

QMap<QString, DataObject* (*)()> DataObjectFactory::typeMap;
DataObject* DataObjectFactory::createInstance(const QString& s)
{
    if(DataObjectFactory::contains(s))
        return DataObjectFactory::typeMap[s]();
    else if(ContextObjectFactory::contains(s))
        return (DataObject*)ContextObjectFactory::createInstance(s, NULL);
    else
        throw(new TypeNotRegisteredException());
}

bool DataObjectFactory::contains(const QString& s)
{
    return DataObjectFactory::typeMap.contains(s) || ContextObjectFactory::contains(s);
}
