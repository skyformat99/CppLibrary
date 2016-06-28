#ifndef TST_SERIALIZER_H
#define TST_SERIALIZER_H

#include <QtCore>
#include <QtTest>
#include <ralph/data/data.h>
#include "testdataobject1.h"

class SerializerTests : public QObject
{
    Q_OBJECT

public:
    SerializerTests();

private:
    QString testXml = "<TestDataObject1><p1>ralph</p1><p2>2</p2><p3>1.1000000000000001</p3><p4>{00000000-0000-0000-0000-000000000000}</p4><subobj><TestDataObject2><p1>franzi</p1></TestDataObject2></subobj><nsubobjs><TestDataObject2><p1>franzi</p1></TestDataObject2><TestDataObject2><p1>rudi</p1></TestDataObject2></nsubobjs><nints><int>0</int><int>1</int><int>2</int></nints><nstrings><QString>bla</QString><QString>ble</QString><QString>bli</QString></nstrings></TestDataObject1>";

private Q_SLOTS:
    void testXmlSerializer_serialize();
    void testXmlSerializer_deserialize();

public slots:
};

#endif // TST_SERIALIZER_H
