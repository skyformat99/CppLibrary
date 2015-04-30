#include <QtCore>
#include <QtTest>
#include <Data/data.h>
#include "testdataobject1.h"

// TODO test threadsafety of datacontext and dataobjects
class DataTest : public QObject
{
    Q_OBJECT

public:
    DataTest();

private:
    bool _slotCalled;

private Q_SLOTS:
    void testDataObjectFactory();
    void testDataObjectValueProperties();
    void testDataObjectObjectProperties();
    void testDataObjectNobjectsProperties();
    void testDataObjectDynSignals();
    void testDataObjectEquals();
    void testXmlStorageContext();

public slots:
    void slot();
};

DataTest::DataTest()
{
}

void DataTest::testDataObjectFactory()
{
    auto context = new DataContext();
    auto dO = DataObjectFactory::createInstance("TestDataObject1", context);
    QVERIFY2(strcmp(dO->metaObject()->className(), "TestDataObject1") == 0, "Object metainformation doesn't match created type");
    delete context;
}

void DataTest::testDataObjectValueProperties()
{
    auto context = new DataContext();

    auto testUuid1 = QUuid::createUuid();
    auto testUuid2 = QUuid::createUuid();

    auto dO = new TestDataObject1(context);
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

    delete context;
}

void DataTest::testDataObjectObjectProperties()
{
    auto context = new DataContext();

    auto dO1 = new TestDataObject1(context);
    dO1->set_p1("ralph");
    auto dO2 = new TestDataObject2(context);
    dO2->set_p1("franzi");

    QVERIFY2(dO1->subobj() == 0, "Pointer not initialized with 0");
    QVERIFY2(dO1->setProperty("subobj", QVariant::fromValue(dO2)), "Set failed");
    QVERIFY2(dO1->subobj() == dO2, "Property not set correctly");
    QVERIFY2(dO1->property("subobj").value<DataObject*>() == (DataObject*)dO2, "Property not got correctly");

    delete context;
}

void DataTest::testDataObjectNobjectsProperties()
{
    auto context = new DataContext();

    auto dO1 = new TestDataObject1(context);
    dO1->set_p1("ralph");
    auto dO2 = new TestDataObject2(context);
    dO2->set_p1("franzi");

    auto list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    auto list2 = dO1->property("nsubobjs").value<QList<TestDataObject2*>>();

    QVERIFY2(list2.length() == 1, "list length is not 1");
    QVERIFY2(list2.at(0)->p1() == "franzi", "list not set correctly");

    delete context;
}

void DataTest::testDataObjectDynSignals()
{
    auto context = new DataContext();

    this->_slotCalled = false;

    auto dO = new TestDataObject1(context);

    QObject::connect(dO, SIGNAL(p1Changed()), this, SLOT(slot()));

    dO->set_p1("franzi");

    QObject::disconnect(dO, SIGNAL(p1Changed()), this, SLOT(slot()));

    QVERIFY2(this->_slotCalled, "Slot was not called");    

    delete context;
}

void DataTest::testDataObjectEquals()
{
    auto context = new DataContext();

    auto dO1 = new TestDataObject1(context);
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    auto dO2 = new TestDataObject1(context);
    dO2->set_p1("ralph");
    dO2->set_p2(2);
    dO2->set_p3(1.1);

    auto dO3 = new TestDataObject1(context);
    dO3->set_p1("franzi");
    dO3->set_p2(2);
    dO3->set_p3(1.1);

    QVERIFY2(dO1->equals(dO2), "objects with same content weren't detected as equal");
    QVERIFY2(!dO1->equals(dO3), "objects with different content were detected as equal");

    delete context;
}

void DataTest::testXmlStorageContext()
{
    QFile file("test.xml");
    auto context1 = new XmlStorageContext(file);
    auto context2 = new XmlStorageContext(file);

    auto dO1 = new TestDataObject1(context1);
    dO1->set_p1("ralph");
    auto dO2 = new TestDataObject2(context1);
    dO2->set_p1("franzi");

    auto list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);
    dO1->set_subobj(dO2);

    context1->saveAll();

    dO2->set_p1("rudi");

    context1->save(dO2->id());

    //auto dO1Copy = context2->get(dO1->id());
    //QVERIFY2(dO1->equals(dO1Copy), "read object does not equal written object");

    delete context1;
    delete context2;
}

void DataTest::slot()
{
    this->_slotCalled = true;
}

QTEST_APPLESS_MAIN(DataTest)

#include "tst_datatest.moc"
