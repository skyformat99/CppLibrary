#ifndef DATAOBJECTFACTORY_H
#define DATAOBJECTFACTORY_H

#include <QtCore>

class DataObject;
class DataContext;

template<typename T> DataObject * createDataObjectInstance(DataContext *context) { return new T(context); }

class DataObjectFactory
{
public:
    static QMap<QString, DataObject*(*)(DataContext*)> typeMap;

    static DataObject * createInstance(const QString &s, DataContext *context);
};

#endif // DATAOBJECTFACTORY_H
