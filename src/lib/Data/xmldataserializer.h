#ifndef XMLDATASERIALIZER_H
#define XMLDATASERIALIZER_H

#include "textdataserializer.h"

class XmlDataSerializer : public TextDataSerializer
{
public:
    XmlDataSerializer();
    ~XmlDataSerializer();

    QString Serialize();
    void Serialize(QFile& file);

    DataObject* Deserialize(QString& text);
    DataObject* Deserialize(QFile& file);
};

#endif // XMLDATASERIALIZER_H
