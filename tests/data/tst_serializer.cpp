#include "tst_serializer.h"

SerializerTests::SerializerTests()
{
}

void SerializerTests::testXmlSerializer_serialize()
{
    QSharedPointer<TestDataObject1> dO1(new TestDataObject1());
    dO1->set_p1("ralph");
    dO1->set_p2(2);
    dO1->set_p3(1.1);

    QSharedPointer<TestDataObject2> dO2(new TestDataObject2());
    dO2->set_p1("franzi");

    QSharedPointer<TestDataObject2> dO3(new TestDataObject2());
    dO3->set_p1("rudi");

    dO1->set_subobj(dO2);

    QList<QSharedPointer<TestDataObject2>> list1 = dO1->nsubobjs();
    list1.append(dO2);
    list1.append(dO3);
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

    ralph::data::XmlSerializer ser;

    QList<int> tmp1 = dO1->nints();
    QList<QVariant> tmp2 = dO1->__g_nints();

    QString xml = ser.serialize(*dO1);

    //qDebug() << xml.replace("\r", "", Qt::CaseSensitive).replace("\n", "", Qt::CaseSensitive).replace(" ", "", Qt::CaseSensitive);  // uncomment, see and replace below if testobjects changed and therefor the resulting xml

    QVERIFY2(xml.replace("\r", "", Qt::CaseSensitive).replace("\n", "", Qt::CaseSensitive).replace(" ", "", Qt::CaseSensitive) == testXml, "Generated xml does not match the template");
}

void SerializerTests::testXmlSerializer_deserialize()
{
    ralph::data::XmlSerializer ser;

    QSharedPointer<TestDataObject1> dO4 = ser.deserialize(testXml).objectCast<TestDataObject1>();

    QVERIFY2(dO4->p1() == "ralph" &&
             dO4->p2() == 2 &&
             dO4->p3() == 1.1 &&
             dO4->subobj() != NULL &&
             dO4->subobj()->p1() == "franzi" &&
             dO4->nsubobjs().count() == 2 && dO4->nsubobjs().at(0)->p1() == "franzi" && dO4->nsubobjs().at(1)->p1() == "rudi" &&
             dO4->nints().count() == 3 && dO4->nints().at(1) == 1 &&
             dO4->nstrings().count() == 3 && dO4->nstrings().at(1) == "ble", "Deserialized object does not match");
}

