#ifndef TESTDATAOBJECT1_H
#define TESTDATAOBJECT1_H

#include <QtCore>
#include <ralph/data/data.h>

#include "testdataobject2.h"

class TestDataObject1 : public DataObject
{
    Q_OBJECT
    DATAOBJECT(TestDataObject1)
    VAL_PROPERTY(QString, p1, "")
    VAL_PROPERTY(int, p2, 0)
    VAL_PROPERTY(double, p3, 0.0)
    VAL_PROPERTY(QUuid, p4, QUuid())
    REF_PROPERTY(TestDataObject2, subobj)
    NREF_PROPERTY(TestDataObject2, nsubobjs)
    NVAL_PROPERTY(int, nints);
    NVAL_PROPERTY(QString, nstrings);
public:
    TestDataObject1();
    ~TestDataObject1();
};

#endif // TESTDATAOBJECT1_H
