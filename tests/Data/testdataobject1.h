#ifndef TESTDATAOBJECT1_H
#define TESTDATAOBJECT1_H

#include <QtCore>
#include <Data/data.h>

#include "testdataobject2.h"

class TestDataObject1 : public DataObject
{
    Q_OBJECT
    DATAOBJECT(TestDataObject1)
    VALUE_PROPERTY(QString, p1, "")
    VALUE_PROPERTY(int, p2, 0)
    VALUE_PROPERTY(double, p3, 0.0)
    VALUE_PROPERTY(QUuid, p4, QUuid())
    OBJECT_PROPERTY(TestDataObject2, subobj)
    NOBJECTS_PROPERTY(TestDataObject2, nsubobjs)
    NVALUES_PROPERTY(int, nints);
    NVALUES_PROPERTY(QString, nstrings);
public:
    TestDataObject1();
    ~TestDataObject1();
};

#endif // TESTDATAOBJECT1_H
