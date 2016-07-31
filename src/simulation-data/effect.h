#ifndef EFFECT_H
#define EFFECT_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class Effect : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(Effect)
    VAL_PROPERTY(QUuid, calculateScriptId, QUuid())
    VAL_PROPERTY(QUuid, aggregateScriptId, QUuid())

    public:
        Effect();
};

#endif // EFFECT_H
