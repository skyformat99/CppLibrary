#ifndef DATAOBJECTFACTORY_H
#define DATAOBJECTFACTORY_H

#include <QtCore>
#include "dataexceptions.h"

namespace ralph {
    namespace data {

        class DataObject;

        template<typename T> DataObject* createDataObjectInstance() { return (DataObject*)(new T()); }

        /// static type managing DataObjects
        class DataObjectFactory
        {
        public:
            /// mapping of DataObject ids and their type
            static QMap<QString, DataObject* (*)()> typeMap;

            /// create an instance of a DataObject type given a certain id
            static DataObject* create(const QString &id);

            /// lookup if a DataObject type with a certain id is registered
            static bool contains(const QString &id);
        };

    }
}

#endif // DATAOBJECTFACTORY_H
