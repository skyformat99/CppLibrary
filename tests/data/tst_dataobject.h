#ifndef DATAOBJECTTESTS_H
#define DATAOBJECTTESTS_H

#include <QtTest>
#include <QtCore>
#include <QtTest>
#include <ralph/data/data.h>
#include "testdataobject1.h"

class DataObjectTests : public QObject
{
    Q_OBJECT

public:
    DataObjectTests();

private:
    bool _testDataObjectDynSignals_slotChangingCalled;
    bool _testDataObjectDynSignals_slotChangedCalled;
    QSharedPointer<TestDataObject1> _testDataObjectDynSignals_Object;

private Q_SLOTS:
    void testDataObjectFactory();
    void testDataObject_valueProperties();
    void testDataObject_objectProperties();
    void testDataObject_nobjectsProperties();
    void testDataObject_nvaluesProperties();
    void testDataObject_dynSignals();
    void testDataObject_equals();
    void testDataObject_updateFrom();
    void testDataObject_clone();
    // TODO think about test cases to check threadsafety and create testDataObject_threadSafety

public slots:
    void testDataObjectDynSignals_slotChanging();
    void testDataObjectDynSignals_slotChanged();
};

#endif // DATAOBJECTTESTS_H
