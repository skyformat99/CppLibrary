#include "dataobjectfactory.h"
#include "contextobjectfactory.h"

QMap<QString, DataObject*(*)()> DataObjectFactory::typeMap;
DataObject * DataObjectFactory::createInstance(const QString &s)
{
    if(DataObjectFactory::hasType(s))
        return DataObjectFactory::typeMap[s]();
    else if(ContextObjectFactory::hasType(s))
        return (DataObject*)ContextObjectFactory::createInstance(s, NULL);
    else
        throw(new TypeNotRegisteredException());
}

bool DataObjectFactory::hasType(const QString &s)
{
    return DataObjectFactory::typeMap.contains(s) || ContextObjectFactory::hasType(s);
}
