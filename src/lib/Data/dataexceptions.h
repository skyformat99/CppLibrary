#ifndef DATAEXCEPTIONS
#define DATAEXCEPTIONS

#include <QtCore>

class DataObjectException
{
public:
    DataObjectException(){}
    ~DataObjectException(){}
};

class TypeNotMatchingException : public DataObjectException
{
public:
    TypeNotMatchingException(){}
    ~TypeNotMatchingException(){}
};

class IdNotMatchingException : public DataObjectException
{
public:
    IdNotMatchingException(){}
    ~IdNotMatchingException(){}
};

class DataContextException
{
public:
    DataContextException(){}
    ~DataContextException(){}
};

class ObjectWithSameIdAlreadyInDataContextException : public DataContextException
{
public:
    ObjectWithSameIdAlreadyInDataContextException(const QUuid& id){this->_id = id;}
    ~ObjectWithSameIdAlreadyInDataContextException(){}

    QUuid id(){return this->_id;}
private:
    QUuid _id;
};

class ObjectNotFoundInDataContextException : public DataContextException
{
public:
    ObjectNotFoundInDataContextException(const QUuid& id){this->_id = id;}
    ~ObjectNotFoundInDataContextException(){}

    QUuid id(){return this->_id;}

private:
    QUuid _id;
};

class CouldNotOpenStorageFileForWrite : public DataContextException
{
public:
    CouldNotOpenStorageFileForWrite(){}
    ~CouldNotOpenStorageFileForWrite(){}
};

class CouldNotOpenStorageFileForRead : public DataContextException
{
public:
    CouldNotOpenStorageFileForRead(){}
    ~CouldNotOpenStorageFileForRead(){}
};

class TypeNotRegisteredException : public DataObjectException
{
public:
    TypeNotRegisteredException(){}
    ~TypeNotRegisteredException(){}
};

#endif // DATAEXCEPTIONS

