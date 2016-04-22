#include "dataexceptions.h"

namespace ralph {
    namespace data {
        DataObjectException::DataObjectException() {}
        DataObjectException::~DataObjectException() {}

        TypeNotMatchingException::TypeNotMatchingException() {qDebug("TypeNotMatchingException");}
        TypeNotMatchingException::~TypeNotMatchingException() {}

        TypeNotRegisteredException::TypeNotRegisteredException() {qDebug("TypeNotRegisteredException");}
        TypeNotRegisteredException::~TypeNotRegisteredException() {}
    }
}
