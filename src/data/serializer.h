#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QtCore>
#include <QtXml>
#include "dataobject.h"

namespace ralph {
    namespace data {

        /// base type for DataObject serializer
        class Serializer
        {
        public:
            Serializer();
            ~Serializer();

            /// serialize into a file
            virtual void Serialize(DataObject &obj, QFile &file) = 0;

            /// serialize into a data stream
            virtual void Serialize(DataObject &obj, QDataStream &stream) = 0;

            /// deserilize from a file
            virtual QSharedPointer<DataObject> Deserialize(QFile &file) = 0;

            /// deserialize from a data stream
            virtual QSharedPointer<DataObject> Deserialize(QDataStream &stream) = 0;
        };

        /// base type for DataObject serializer serializing into a text based dataformat
        class TextSerializer: public Serializer
        {
        public:
            TextSerializer();
            ~TextSerializer();

            /// serialize into a string
            virtual QString Serialize(DataObject &obj) = 0;
            virtual void Serialize(DataObject &obj, QFile &file) = 0;
            virtual void Serialize(DataObject &obj, QDataStream &stream) = 0;

            /// deserialize from a string
            virtual QSharedPointer<DataObject> Deserialize(QString &text) = 0;
            virtual QSharedPointer<DataObject> Deserialize(QFile &file) = 0;
            virtual QSharedPointer<DataObject> Deserialize(QDataStream &stream) = 0;
        };

        /// serializer serializing DataObjects into xml
        class XmlSerializer: public TextSerializer
        {
        public:
            XmlSerializer();
            ~XmlSerializer();

            QString Serialize(DataObject &obj);
            void Serialize(DataObject &obj, QFile &file);
            void Serialize(DataObject &obj, QDataStream &stream);

            QSharedPointer<DataObject> Deserialize(QString &text);
            QSharedPointer<DataObject> Deserialize(QFile &file);
            QSharedPointer<DataObject> Deserialize(QDataStream &stream);

        private:
            void Serialize(DataObject &obj, QDomDocument &doc);
            void Serialize(DataObject &obj, QDomDocument &doc, QDomNode &parent);
            void SerializeContent(DataObject &obj, QDomDocument &doc, QDomNode &node);

            DataObject* Deserialize(QDomDocument &doc);
            DataObject* Deserialize(QDomNode &node);
            void DeserializeContent(QDomNode &node, DataObject &obj);
        };

        // TODO implement JsonSerializer for DataObjects
        /// serializer serializing DataObjects into JSON (not implemented at the moment)
        class JsonSerializer: public TextSerializer
        {
        public:
            JsonSerializer();
            ~JsonSerializer();

            QString Serialize(DataObject &obj);
            void Serialize(DataObject &obj, QFile &file);
            void Serialize(DataObject &obj, QDataStream &stream);

            QSharedPointer<DataObject> Deserialize(QString &text);
            QSharedPointer<DataObject> Deserialize(QFile &file);
            QSharedPointer<DataObject> Deserialize(QDataStream &stream);

        private:
        };

    }
}

#endif // SERIALIZER_H
