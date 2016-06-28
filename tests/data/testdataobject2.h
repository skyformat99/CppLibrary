#ifndef TESTDATAOBJECT2_H
#define TESTDATAOBJECT2_H

#include <QtCore>
#include <ralph/data/dataobject.h>

class TestDataObject2 : public ralph::data::DataObject
{
    Q_OBJECT
    DATAOBJECT(TestDataObject2)
    VAL_PROPERTY(QString, p1, "")
public:
    TestDataObject2();
    ~TestDataObject2();
};

#endif // TESTDATAOBJECT2_H
