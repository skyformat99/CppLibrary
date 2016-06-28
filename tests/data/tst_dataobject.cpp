#include "tst_dataobject.h"

DataObjectTests::DataObjectTests()
{
}

void DataObjectTests::testDataObjectFactory()
{
    QSharedPointer<ralph::data::DataObject> dO(ralph::data::DataObjectFactory::create("TestDataObject1"));
    QVERIFY2(strcmp(dO->metaObject()->className(), "TestDataObject1") == 0, "Object metainformation doesn't match created type");
}

void DataObjectTests::testDataObject_valueProperties()
{
    QUuid testUuid1 = QUuid::createUuid();
    QUuid testUuid2 = QUuid::createUuid();

    QSharedPointer<TestDataObject1> dO(new TestDataObject1());
    dO->set_p1("ralph");
    dO->set_p2(2);
    dO->set_p3(1.1);
    dO->set_p4(testUuid1);

    QVERIFY2(dO->setProperty("p1", "franzi"), "Set failed");
    QVERIFY2(dO->p1() == "franzi", "Property not set correctly");
    QVERIFY2(dO->property("p1") == "franzi", "Property not got correctly");

    QVERIFY2(dO->setProperty("p2", 5), "Set failed");
    QVERIFY2(dO->p2() == 5, "Property not set correctly");
    QVERIFY2(dO->property("p2") == 5, "Property not got correctly");

    QVERIFY2(dO->setProperty("p3", 2.2), "Set failed");
    QVERIFY2(dO->p3() == 2.2, "Property not set correctly");
    QVERIFY2(dO->property("p3") == 2.2, "Property not got correctly");

    QVERIFY2(dO->setProperty("p4", testUuid2), "Set failed");
    QVERIFY2(dO->p4() == testUuid2, "Property not set correctly");
    QVERIFY2(dO->property("p4") == testUuid2, "Property not got correctly");
}

void DataObjectTests::testDataObject_objectProperties()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    QSharedPointer<TestDataObject2> dO2(new TestDataObject2());
    dO2->set_p1("franzi");

    QVERIFY2(dO1->subobj() == 0, "Pointer not initialized with 0");
    QVERIFY2(dO1->setProperty("subobj", QVariant::fromValue(dO2)), "Set failed");
    QVERIFY2(dO1->subobj() == dO2, "Property not set correctly");
    QVERIFY2(dO1->property("subobj").value<QSharedPointer<TestDataObject2>>() == dO2, "Property not got correctly");
}

void DataObjectTests::testDataObject_nobjectsProperties()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    QSharedPointer<TestDataObject2> dO2(new TestDataObject2());
    dO2->set_p1("franzi");

    QList<QSharedPointer<TestDataObject2>> list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    //QList<QSharedPointer<TestDataObject2>> list2 = dO1->property("nsubobjs").value<QList<QSharedPointer<TestDataObject2>>>();
    QList<QSharedPointer<TestDataObject2>> list2 = dO1->nsubobjs();

    QVERIFY2(list2.length() == 1, "list length is not 1");
    QVERIFY2(list2.at(0)->p1() == "franzi", "list not set correctly");
}

void DataObjectTests::testDataObject_nvaluesProperties()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");

    QList<int> list1 = dO1->nints();
    list1.append(0);
    list1.append(1);
    list1.append(2);
    dO1->set_nints(list1);

    QList<QString> list2 = dO1->nstrings();
    list2.append("bla");
    list2.append("ble");
    list2.append("bli");
    dO1->set_nstrings(list2);

    QList<int> list3 = dO1->property("nints").value<QList<int>>();
    QList<QString> list4 = dO1->property("nstrings").value<QList<QString>>();

    QVERIFY2(list3.length() == 3 && list4.length() == 3, "list length is not 3");
    QVERIFY2(list3.at(2) == 2 && list4.at(2) == "bli", "list not set correctly");
}

void DataObjectTests::testDataObject_dynSignals()
{
    this->_testDataObjectDynSignals_slotChangingCalled = false;
    this->_testDataObjectDynSignals_slotChangedCalled = false;

    this->_testDataObjectDynSignals_Object = QSharedPointer<TestDataObject1>(new TestDataObject1());

    this->_testDataObjectDynSignals_Object->set_p1("rudi");

    QObject::connect(this->_testDataObjectDynSignals_Object.data(), SIGNAL(p1Changing()), this, SLOT(testDataObjectDynSignals_slotChanging()));
    QObject::connect(this->_testDataObjectDynSignals_Object.data(), SIGNAL(p1Changed()), this, SLOT(testDataObjectDynSignals_slotChanged()));

    this->_testDataObjectDynSignals_Object->set_p1("franzi");

    QObject::disconnect(this->_testDataObjectDynSignals_Object.data(), SIGNAL(p1Changing()), this, SLOT(testDataObjectDynSignals_slotChanging()));
    QObject::disconnect(this->_testDataObjectDynSignals_Object.data(), SIGNAL(p1Changed()), this, SLOT(testDataObjectDynSignals_slotChanged()));

    QVERIFY2(this->_testDataObjectDynSignals_slotChangingCalled, "changing slot was not called");
    QVERIFY2(this->_testDataObjectDynSignals_slotChangedCalled, "changed slot was not called");
}

void DataObjectTests::testDataObject_equals()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    QSharedPointer<TestDataObject1> dO2(new TestDataObject1());
    dO2->set_p1("ralph");
    dO2->set_p2(2);
    dO2->set_p3(1.1);

    QSharedPointer<TestDataObject1> dO3(new TestDataObject1());
    dO3->set_p1("franzi");
    dO3->set_p2(2);
    dO3->set_p3(1.1);

    QVERIFY2(dO1->equals(*dO2), "objects with same content weren't detected as equal");
    QVERIFY2(!dO1->equals(*dO3), "objects with different content were detected as equal");
}

void DataObjectTests::testDataObject_updateFrom()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    QSharedPointer<TestDataObject1> dO2(new TestDataObject1());
    dO2->set_p1("franzi");
    dO2->set_p2(2);
    dO2->set_p3(1.1);

    dO2->updateFrom(*dO1);

    QVERIFY2(dO1->equals(*dO2), "objects with same content weren't detected as equal");
}

void DataObjectTests::testDataObject_clone()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    QSharedPointer<TestDataObject1> dO2 = dO1->clone().staticCast<TestDataObject1>();

    QVERIFY2(dO1->equals(*dO2), "objects with same content weren't detected as equal");
}

void DataObjectTests::testDataObjectDynSignals_slotChanging()
{
    this->_testDataObjectDynSignals_slotChangingCalled = true;

    QVERIFY2(this->_testDataObjectDynSignals_Object->p1() == "rudi", "changing slot was called, but property is already changed");
}

void DataObjectTests::testDataObjectDynSignals_slotChanged()
{
    this->_testDataObjectDynSignals_slotChangedCalled = true;
}
