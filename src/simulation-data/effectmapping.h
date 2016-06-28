#ifndef EFFECTMAPPING_H
#define EFFECTMAPPING_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class EffectMapping : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(EffectMapping)
    VAL_PROPERTY(QUuid, effectId, QUuid())
    VAL_PROPERTY(QUuid, affectingSystemId, QUuid())
    VAL_PROPERTY(QUuid, affectedSystemId, QUuid())

    public:
        EffectMapping();
};

#endif // EFFECTMAPPING_H
