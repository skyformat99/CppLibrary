#ifndef TEXTDATASERIALIZER
#define TEXTDATASERIALIZER

#include <QtCore>
#include "dataobject.h"

class TextDataSerializer
{
public:
    virtual QString Serialize() = 0;
    virtual void Serialize(QFile& file) = 0;

    virtual DataObject* Deserialize(QString& text) = 0;
    virtual DataObject* Deserialize(QFile& file) = 0;
};

#endif // TEXTDATASERIALIZER

