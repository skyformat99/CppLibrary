#include "testcontextobject1.h"

CONTEXTOBJECT_REGISTER(TestContextObject1)

TestContextObject1::TestContextObject1(DataContext* context) : ContextObject(context)
{
}

TestContextObject1::~TestContextObject1()
{
}
