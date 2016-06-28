#ifndef SIMULATIONDESCRIPTION_H
#define SIMULATIONDESCRIPTION_H

#include <QtCore>
#include <ralph/data/dataobject.h>

#include "systemmapping.h"

class SimulationDescription : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(SimulationDescription)
    VAL_PROPERTY(uint, obstacle, 0)
    VAL_PROPERTY(bool, useDouble, true)
    NREF_PROPERTY(SystemMapping, systems)
    NREF_PROPERTY(EffectMapping, effects)

    public:
        SimulationDescription();
};

#endif // SIMULATIONDESCRIPTION_H
