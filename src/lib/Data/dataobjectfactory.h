#ifndef DATAOBJECTFACTORY_H
#define DATAOBJECTFACTORY_H

#include <QtCore>
#include "dataexceptions.h"

class DataObject;

template<typename T> DataObject* createDataObjectInstance() { return (DataObject*)(new T()); }

class DataObjectFactory
{
public:
    static QMap<QString, DataObject* (*)()> typeMap;

    static DataObject* create(const QString& s);
    static bool contains(const QString& s);
};

#endif // DATAOBJECTFACTORY_H
