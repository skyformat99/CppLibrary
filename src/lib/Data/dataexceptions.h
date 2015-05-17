#ifndef DATAEXCEPTIONS
#define DATAEXCEPTIONS

#include <QtCore>

class DataObjectException
{
public:
    DataObjectException(){qDebug("DataObjectException");}
    ~DataObjectException(){}
};

class TypeNotMatchingException : public DataObjectException
{
public:
    TypeNotMatchingException(){qDebug("TypeNotMatchingException");}
    ~TypeNotMatchingException(){}
};

class TypeNotRegisteredException : public DataObjectException
{
public:
    TypeNotRegisteredException(){qDebug("TypeNotRegisteredException");}
    ~TypeNotRegisteredException(){}
};

#endif // DATAEXCEPTIONS

