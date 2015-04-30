#include "dataobjectfactory.h"

QMap<QString, DataObject*(*)()> DataObjectFactory::typeMap;
DataObject * DataObjectFactory::createInstance(const QString &s)
{
    return DataObjectFactory::typeMap[s]();
}
