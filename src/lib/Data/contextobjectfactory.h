#ifndef CONTEXTOBJECTFACTORY_H
#define CONTEXTOBJECTFACTORY_H

#include <QtCore>

class ContextObject;
class DataContext;

template<typename T> ContextObject * createContextObjectInstance(DataContext *context) { return new T(context); }

class ContextObjectFactory
{
public:
    static QMap<QString, ContextObject*(*)(DataContext*)> typeMap;

    static ContextObject * createInstance(const QString &s, DataContext *context);
};

#endif // CONTEXTOBJECTFACTORY_H
