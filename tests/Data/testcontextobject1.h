#ifndef TESTCONTEXTOBJECT1_H
#define TESTCONTEXTOBJECT1_H

#include <QtCore>
#include <Data/data.h>

#include "testcontextobject2.h"

class TestContextObject1 : public ContextObject
{
    Q_OBJECT
    CONTEXTOBJECT(TestContextObject1)
    VALUE_PROPERTY(QString, p1, "")
    VALUE_PROPERTY(int, p2, 0)
    VALUE_PROPERTY(double, p3, 0.0)
    VALUE_PROPERTY(QUuid, p4, QUuid())
    OBJECT_PROPERTY(TestContextObject2, subobj)
    NOBJECTS_PROPERTY(TestContextObject2, nsubobjs)
public:
    TestContextObject1(DataContext* context);
    ~TestContextObject1();
};

#endif // TESTCONTEXTOBJECT1_H
