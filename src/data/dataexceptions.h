#ifndef DATAEXCEPTIONS
#define DATAEXCEPTIONS

#include <QtCore>

namespace ralph {
    namespace data {

        /// base type for exceptions concerning data
        class DataObjectException
        {
        public:
            DataObjectException();
            ~DataObjectException();
        };

        /// exception thrown if an operation needs two DataObjects of the same type but not given
        class TypeNotMatchingException : public DataObjectException
        {
        public:
            TypeNotMatchingException();
            ~TypeNotMatchingException();
        };

        /// exception thrown on trying to access a DataObject type not existing/registered
        class TypeNotRegisteredException : public DataObjectException
        {
        public:
            TypeNotRegisteredException();
            ~TypeNotRegisteredException();
        };

    }
}

#endif // DATAEXCEPTIONS

