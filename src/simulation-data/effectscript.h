#ifndef EFFECTSCRIPT_H
#define EFFECTSCRIPT_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class EffectScript : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(EffectScript)
    VAL_PROPERTY(QString, type, QString("ecl"))
    VAL_PROPERTY(QString, content, QString())

    public:
        EffectScript();
};

#endif // EFFECTSCRIPT_H
