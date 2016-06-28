#ifndef PROPERTYVALUE_H
#define PROPERTYVALUE_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class PropertyValue : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(PropertyValue)
    VAL_PROPERTY(QUuid, propertyId, QUuid())
    VAL_PROPERTY(double, value, 0.0)

    public:
        PropertyValue();
};

#endif // PROPERTYVALUE_H
