
#include <QtCore>
#include <QtTest>
#include <Data/data.h>
#include "testdataobject1.h"

class DataObjectTests : public QObject
{
    Q_OBJECT

public:
    DataObjectTests();

private:
    bool _slotCalled;

private Q_SLOTS:
    void testDataObjectFactory();
    void testDataObjectValueProperties();
    void testDataObjectObjectProperties();
    void testDataObjectNobjectsProperties();
    void testDataObjectNvaluesProperties();
    void testDataObjectDynSignals();
    void testDataObjectEquals();
    void testXmlSerializer();

public slots:
    void slot();
};

DataObjectTests::DataObjectTests()
{
}

void DataObjectTests::testDataObjectFactory()
{
    auto dO = DataObjectFactory::create("TestDataObject1");
    QVERIFY2(strcmp(dO->metaObject()->className(), "TestDataObject1") == 0, "Object metainformation doesn't match created type");
    delete dO;
}

void DataObjectTests::testDataObjectValueProperties()
{
    auto testUuid1 = QUuid::createUuid();
    auto testUuid2 = QUuid::createUuid();

    auto dO = new TestDataObject1();
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

    delete dO;
}

void DataObjectTests::testDataObjectObjectProperties()
{
    auto dO1 = new TestDataObject1();
    dO1->set_p1("ralph");
    auto dO2 = new TestDataObject2();
    dO2->set_p1("franzi");

    QVERIFY2(dO1->subobj() == 0, "Pointer not initialized with 0");
    QVERIFY2(dO1->setProperty("subobj", QVariant::fromValue(dO2)), "Set failed");
    QVERIFY2(dO1->subobj() == dO2, "Property not set correctly");
    QVERIFY2(dO1->property("subobj").value<DataObject*>() == (DataObject*)dO2, "Property not got correctly");

    delete dO1;
    delete dO2;
}

void DataObjectTests::testDataObjectNobjectsProperties()
{
    auto dO1 = new TestDataObject1();
    dO1->set_p1("ralph");
    auto dO2 = new TestDataObject2();
    dO2->set_p1("franzi");

    auto list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    auto list2 = dO1->property("nsubobjs").value<QList<TestDataObject2*>>();

    QVERIFY2(list2.length() == 1, "list length is not 1");
    QVERIFY2(list2.at(0)->p1() == "franzi", "list not set correctly");

    delete dO1;
    delete dO2;
}

void DataObjectTests::testDataObjectNvaluesProperties()
{
    auto dO1 = new TestDataObject1();
    dO1->set_p1("ralph");

    auto list1 = dO1->nints();
    list1.append(0);
    list1.append(1);
    list1.append(2);
    dO1->set_nints(list1);

    auto list2 = dO1->nstrings();
    list2.append("bla");
    list2.append("ble");
    list2.append("bli");
    dO1->set_nstrings(list2);

    auto list3 = dO1->property("nints").value<QList<int>>();
    auto list4 = dO1->property("nstrings").value<QList<QString>>();

    QVERIFY2(list3.length() == 3 && list4.length() == 3, "list length is not 3");
    QVERIFY2(list3.at(2) == 2 && list4.at(2) == "bli", "list not set correctly");

    delete dO1;
}

void DataObjectTests::testDataObjectDynSignals()
{
    this->_slotCalled = false;

    auto dO = new TestDataObject1();

    QObject::connect(dO, SIGNAL(p1Changed()), this, SLOT(slot()));

    dO->set_p1("franzi");

    QObject::disconnect(dO, SIGNAL(p1Changed()), this, SLOT(slot()));

    QVERIFY2(this->_slotCalled, "Slot was not called");

    delete dO;
}

void DataObjectTests::testDataObjectEquals()
{
    auto dO1 = new TestDataObject1();
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    auto dO2 = new TestDataObject1();
    dO2->set_p1("ralph");
    dO2->set_p2(2);
    dO2->set_p3(1.1);

    auto dO3 = new TestDataObject1();
    dO3->set_p1("franzi");
    dO3->set_p2(2);
    dO3->set_p3(1.1);

    QVERIFY2(dO1->equals(*dO2), "objects with same content weren't detected as equal");
    QVERIFY2(!dO1->equals(*dO3), "objects with different content were detected as equal");

    delete dO1;
    delete dO2;
}

void DataObjectTests::testXmlSerializer()
{
    auto dO1 = new TestDataObject1();
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    auto dO2 = new TestDataObject2();
    dO2->set_p1("franzi");

    dO1->set_subobj(dO2);

    auto list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    auto list2 = dO1->nints();
    list2.append(0);
    list2.append(1);
    list2.append(2);
    dO1->set_nints(list2);

    auto list3 = dO1->nstrings();
    list3.append("bla");
    list3.append("ble");
    list3.append("bli");
    dO1->set_nstrings(list3);

    XmlDataSerializer ser;

    auto xml = ser.Serialize(*dO1);

    //qDebug() << xml;  // uncomment, see and replace below if testobjects changed and therefor the resulting xml
    QString temp("<TestDataObject1><p1>ralph</p1><p2>2</p2><p3>1.1</p3><p4>{00000000-0000-0000-0000-000000000000}</p4><subobj><TestDataObject2><p1>franzi</p1></TestDataObject2></subobj><nsubobjs><TestDataObject2><p1>franzi</p1></TestDataObject2></nsubobjs><nints><int>0</int><int>1</int><int>2</int></nints><nstrings><QString>bla</QString><QString>ble</QString><QString>bli</QString></nstrings></TestDataObject1>");

    QVERIFY2(xml.replace("\r", "", Qt::CaseSensitive).replace("\n", "", Qt::CaseSensitive).replace(" ", "", Qt::CaseSensitive) == temp, "Generated xml does not match the template");

    auto dO3 = (TestDataObject1*)ser.Deserialize(temp);

    QVERIFY2(dO3->p1() == "ralph" &&
             dO3->p2() == 2 &&
             dO3->p3() == 1.1 &&
             dO1->subobj() != NULL &&
             dO1->subobj()->p1() == "franzi" &&
             dO1->nsubobjs().count() == 1 && dO1->nsubobjs().at(0)->p1() == "franzi" &&
             dO1->nints().count() == 3 && dO1->nints().at(1) == 1 &&
             dO1->nstrings().count() == 3 && dO1->nstrings().at(1) == "ble", "Deserialized object does not match");

    delete dO1;
    delete dO2;
    delete dO3;
}

void DataObjectTests::slot()
{
    this->_slotCalled = true;
}

QTEST_APPLESS_MAIN(DataObjectTests)

#include "tst_dataobject.moc"
