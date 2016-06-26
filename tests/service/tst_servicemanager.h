#ifndef TST_SERVICEMANAGER_H
#define TST_SERVICEMANAGER_H

#include <QtCore>
#include <QtTest>

using namespace ralph::service;

class ServiceManagerTests : public QObject
{
    Q_OBJECT

public:
    SerializerTests();

private:

private Q_SLOTS:
    void createService();

public slots:
};

#endif // TST_SERVICEMANAGER_H
