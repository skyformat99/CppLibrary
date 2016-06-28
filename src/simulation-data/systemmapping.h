#ifndef SYSTEMMAPPING_H
#define SYSTEMMAPPING_H

#include <QtCore>
#include <ralph/data/dataobject.h>

#include "propertyvalue.h"
#include "effectmapping.h"

/// maps the instance of a system to a simulation description. it contains the properties and effects to use
class SystemMapping : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(SystemMapping)
    VAL_PROPERTY(QUuid, system, QUuid())
    NREF_PROPERTY(PropertyValue, properties)

    public:
        SystemMapping();
};

#endif // SYSTEMMAPPING_H
