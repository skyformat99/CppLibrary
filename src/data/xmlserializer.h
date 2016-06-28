#ifndef XMLSERIALIZER_H
#define XMLSERIALIZER_H

#include <QtCore>
#include <QtXml>
#include "dataobject.h"
#include "serializer.h"

namespace ralph {
    namespace data {
        /// serializer serializing DataObjects into xml
        class XmlSerializer: public TextSerializer
        {
        public:
            XmlSerializer();
            ~XmlSerializer();

            QString serialize(DataObject &obj);
            void serialize(DataObject &obj, QFile &file);
            void serialize(DataObject &obj, QDataStream &stream);

            QSharedPointer<DataObject> deserialize(QString &text);
            QSharedPointer<DataObject> deserialize(QFile &file);
            QSharedPointer<DataObject> deserialize(QDataStream &stream);

        private:
            void serialize(DataObject &obj, QDomDocument &doc);
            void serialize(DataObject &obj, QDomDocument &doc, QDomNode &parent);
            void serializeContent(DataObject &obj, QDomDocument &doc, QDomNode &node);

            DataObject* deserialize(QDomDocument &doc);
            DataObject* deserialize(QDomNode &node);
            void deserializeContent(QDomNode &node, DataObject &obj);
        };
    }
}

#endif // XMLSERIALIZER_H
