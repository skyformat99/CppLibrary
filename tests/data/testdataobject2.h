#ifndef TESTDATAOBJECT2_H
#define TESTDATAOBJECT2_H

#include <QtCore>
#include <ralph/data/data.h>

using namespace ralph::data;

class TestDataObject2 : public DataObject
{
    Q_OBJECT
    DATAOBJECT(TestDataObject2)
    VAL_PROPERTY(QString, p1, "")
public:
    TestDataObject2();
    ~TestDataObject2();
};

#endif // TESTDATAOBJECT2_H
