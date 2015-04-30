#ifndef TESTCONTEXTOBJECT2_H
#define TESTCONTEXTOBJECT2_H

#include <QtCore>
#include <Data/data.h>

class TestContextObject2 : public ContextObject
{
    Q_OBJECT
    CONTEXTOBJECT(TestContextObject2)
    VALUE_PROPERTY(QString, p1, "")
public:
    TestContextObject2(DataContext* context);
    ~TestContextObject2();
};

#endif // TESTCONTEXTOBJECT2_H
