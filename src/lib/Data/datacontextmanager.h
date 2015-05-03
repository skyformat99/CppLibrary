#ifndef DATACONTEXTMANAGER_H
#define DATACONTEXTMANAGER_H

#include <QtCore>

class DataContext;

class DataContextManager
{
public:
    DataContextManager();
    ~DataContextManager();

    static DataContextManager& instance();

    void add(DataContext& context);
    void remove(DataContext& context);
    QList<DataContext*> getAll() const;

private:
    static DataContextManager s_instance;
    QList<DataContext*> _contexts;
    mutable QMutex _mutex;
};

#endif // DATACONTEXTMANAGER_H
