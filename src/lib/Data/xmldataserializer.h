#ifndef XMLDATASERIALIZER_H
#define XMLDATASERIALIZER_H

#include <QtCore>
#include <QtXml>
#include "dataobject.h"

class XmlDataSerializer
{
public:
    XmlDataSerializer();
    ~XmlDataSerializer();

    QString Serialize(DataObject& obj);
    void Serialize(DataObject& obj, QFile& file);

    DataObject* Deserialize(QString& text);
    DataObject* Deserialize(QFile& file);

private:
    void Serialize(DataObject& obj, QDomDocument& doc);
    void Serialize(DataObject& obj, QDomDocument& doc, QDomNode& parent);
    void SerializeContent(DataObject& obj, QDomDocument& doc, QDomNode& node);

    DataObject* Deserialize(QDomDocument& doc);
    DataObject* Deserialize(QDomNode& node);
    void DeserializeContent(QDomNode& node, DataObject& obj);
};

#endif // XMLDATASERIALIZER_H
