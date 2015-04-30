#include "contextobjectfactory.h"

QMap<QString, ContextObject*(*)(DataContext*)> ContextObjectFactory::typeMap;
ContextObject * ContextObjectFactory::createInstance(const QString &s, DataContext *context)
{
    return ContextObjectFactory::typeMap[s](context);
}
