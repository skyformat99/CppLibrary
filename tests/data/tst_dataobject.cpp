
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
    void testDataObjectValueProperties();
    void testDataObjectObjectProperties();
    void testDataObjectNobjectsProperties();
    void testDataObjectNvaluesProperties();
    void testDataObjectDynSignals();
    void testDataObjectEquals();
    void testXmlSerializer();

public slots:
    void testDataObjectDynSignals_slotChanging();
    void testDataObjectDynSignals_slotChanged();
};

DataObjectTests::DataObjectTests()
{
}

void DataObjectTests::testDataObjectFactory()
{
    QSharedPointer<DataObject> dO(DataObjectFactory::create("TestDataObject1"));
    QVERIFY2(strcmp(dO->metaObject()->className(), "TestDataObject1") == 0, "Object metainformation doesn't match created type");
}

void DataObjectTests::testDataObjectValueProperties()
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

void DataObjectTests::testDataObjectObjectProperties()
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

void DataObjectTests::testDataObjectNobjectsProperties()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    QSharedPointer<TestDataObject2> dO2(new TestDataObject2());
    dO2->set_p1("franzi");

    QList<QSharedPointer<TestDataObject2>> list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    QList<QSharedPointer<TestDataObject2>> list2 = dO1->property("nsubobjs").value<QList<QSharedPointer<TestDataObject2>>>();

    QVERIFY2(list2.length() == 1, "list length is not 1");
    QVERIFY2(list2.at(0)->p1() == "franzi", "list not set correctly");
}

void DataObjectTests::testDataObjectNvaluesProperties()
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

void DataObjectTests::testDataObjectDynSignals()
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

void DataObjectTests::testDataObjectEquals()
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

void DataObjectTests::testXmlSerializer()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    QSharedPointer<TestDataObject2> dO2(new TestDataObject2());
    dO2->set_p1("franzi");

    dO1->set_subobj(dO2);

    QList<QSharedPointer<TestDataObject2>> list1 = dO1->nsubobjs();
    list1.append(dO2);
    dO1->set_nsubobjs(list1);

    QList<int> list2 = dO1->nints();
    list2.append(0);
    list2.append(1);
    list2.append(2);
    dO1->set_nints(list2);

    QList<QString> list3 = dO1->nstrings();
    list3.append("bla");
    list3.append("ble");
    list3.append("bli");
    dO1->set_nstrings(list3);

    XmlDataSerializer ser;

    QList<int> tmp1 = dO1->nints();
    QList<QVariant> tmp2 = dO1->__g_nints();

    QString xml = ser.Serialize(*dO1);

    //qDebug() << xml;  // uncomment, see and replace below if testobjects changed and therefor the resulting xml
    QString temp("<TestDataObject1><p1>ralph</p1><p2>2</p2><p3>1.1</p3><p4>{00000000-0000-0000-0000-000000000000}</p4><subobj><TestDataObject2><p1>franzi</p1></TestDataObject2></subobj><nsubobjs><TestDataObject2><p1>franzi</p1></TestDataObject2></nsubobjs><nints><int>0</int><int>1</int><int>2</int></nints><nstrings><QString>bla</QString><QString>ble</QString><QString>bli</QString></nstrings></TestDataObject1>");

    QVERIFY2(xml.replace("\r", "", Qt::CaseSensitive).replace("\n", "", Qt::CaseSensitive).replace(" ", "", Qt::CaseSensitive) == temp, "Generated xml does not match the template");

    QSharedPointer<TestDataObject1> dO3 = ser.Deserialize(temp).objectCast<TestDataObject1>();

    QVERIFY2(dO3->p1() == "ralph" &&
             dO3->p2() == 2 &&
             dO3->p3() == 1.1 &&
             dO1->subobj() != NULL &&
             dO1->subobj()->p1() == "franzi" &&
             dO1->nsubobjs().count() == 1 && dO1->nsubobjs().at(0)->p1() == "franzi" &&
             dO1->nints().count() == 3 && dO1->nints().at(1) == 1 &&
             dO1->nstrings().count() == 3 && dO1->nstrings().at(1) == "ble", "Deserialized object does not match");
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

QTEST_APPLESS_MAIN(DataObjectTests)

#include "tst_dataobject.moc"
