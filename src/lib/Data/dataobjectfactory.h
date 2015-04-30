#ifndef DATAOBJECTFACTORY_H
#define DATAOBJECTFACTORY_H

#include <QtCore>

class DataObject;

template<typename T> DataObject * createDataObjectInstance() { return new T(); }

class DataObjectFactory
{
public:
    static QMap<QString, DataObject*(*)()> typeMap;

    static DataObject * createInstance(const QString &s);
};

#endif // DATAOBJECTFACTORY_H
