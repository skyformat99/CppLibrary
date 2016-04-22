#include "dataobjectfactory.h"

namespace ralph {
    namespace data {

        QMap<QString, DataObject* (*)()> DataObjectFactory::typeMap;
        DataObject* DataObjectFactory::create(const QString& s)
        {
            if(DataObjectFactory::contains(s))
                return DataObjectFactory::typeMap[s]();
            else
                throw(new TypeNotRegisteredException());
        }

        bool DataObjectFactory::contains(const QString& s)
        {
            return DataObjectFactory::typeMap.contains(s);
        }

    }
}
