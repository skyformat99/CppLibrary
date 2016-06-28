#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QtCore>
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
            virtual void serialize(DataObject &obj, QFile &file) = 0;

            /// serialize into a data stream
            virtual void serialize(DataObject &obj, QDataStream &stream) = 0;

            /// deserilize from a file
            virtual QSharedPointer<DataObject> deserialize(QFile &file) = 0;

            /// deserialize from a data stream
            virtual QSharedPointer<DataObject> deserialize(QDataStream &stream) = 0;
        };

        /// base type for DataObject serializer serializing into a text based dataformat
        class TextSerializer: public Serializer
        {
        public:
            TextSerializer();
            ~TextSerializer();

            /// serialize into a string
            virtual QString serialize(DataObject &obj) = 0;
            virtual void serialize(DataObject &obj, QFile &file) = 0;
            virtual void serialize(DataObject &obj, QDataStream &stream) = 0;

            /// deserialize from a string
            virtual QSharedPointer<DataObject> deserialize(QString &text) = 0;
            virtual QSharedPointer<DataObject> deserialize(QFile &file) = 0;
            virtual QSharedPointer<DataObject> deserialize(QDataStream &stream) = 0;
        };

/*        // TODO implement JsonSerializer for DataObjects
        /// serializer serializing DataObjects into JSON (not implemented at the moment)
        class JsonSerializer: public TextSerializer
        {
        public:
            JsonSerializer();
            ~JsonSerializer();

            QString serialize(DataObject &obj);
            void serialize(DataObject &obj, QFile &file);
            void serialize(DataObject &obj, QDataStream &stream);

            QSharedPointer<DataObject> deserialize(QString &text);
            QSharedPointer<DataObject> deserialize(QFile &file);
            QSharedPointer<DataObject> deserialize(QDataStream &stream);

        private:
        };*/
    }
}

#endif // SERIALIZER_H
