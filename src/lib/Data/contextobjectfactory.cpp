#include "contextobjectfactory.h"

QMap<QString, ContextObject* (*)(DataContext*)> ContextObjectFactory::typeMap;
ContextObject* ContextObjectFactory::createInstance(const QString& s, DataContext* context)
{
    if(ContextObjectFactory::contains(s))
        return ContextObjectFactory::typeMap[s](context);
    else
        throw(new TypeNotRegisteredException());
}

bool ContextObjectFactory::contains(const QString& s)
{
    return ContextObjectFactory::typeMap.contains(s);
}
