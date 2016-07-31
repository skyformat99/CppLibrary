#ifndef SIMULATIONDESCRIPTION_H
#define SIMULATIONDESCRIPTION_H

#include <QtCore>
#include <ralph/data/dataobject.h>

#include "systemmapping.h"
#include "effectmapping.h"
#include "effect.h"
#include "effectscript.h"
#include "scriptlibrary.h"

class SimulationDescription : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(SimulationDescription)
    VAL_PROPERTY(uint, obstacle, 0)
    VAL_PROPERTY(bool, useDouble, true)

    NREF_PROPERTY(SystemMapping, systemMappings)
    NREF_PROPERTY(EffectMapping, effectMappings)

    NREF_PROPERTY(Effect, effects)
    NREF_PROPERTY(EffectScript, effectScripts)
    NREF_PROPERTY(ScriptLibrary, scriptLibraries)

    public:
        SimulationDescription();
};

#endif // SIMULATIONDESCRIPTION_H
