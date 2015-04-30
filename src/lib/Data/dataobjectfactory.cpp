#include "dataobjectfactory.h"

QMap<QString, DataObject*(*)(DataContext*)> DataObjectFactory::typeMap;
DataObject * DataObjectFactory::createInstance(const QString &s, DataContext *context)
{
    return DataObjectFactory::typeMap[s](context);
}
