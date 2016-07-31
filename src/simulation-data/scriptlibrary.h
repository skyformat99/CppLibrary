#ifndef SCRIPTLIBRARY_H
#define SCRIPTLIBRARY_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class ScriptLibrary : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(ScriptLibrary)
    VAL_PROPERTY(QString, type, QString("ecl"))
    VAL_PROPERTY(QString, content, QString())

    public:
        ScriptLibrary();
};

#endif // SCRIPTLIBRARY_H
