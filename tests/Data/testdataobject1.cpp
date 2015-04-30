#include "testdataobject1.h"

DATAOBJECT_REGISTER(TestDataObject1)

TestDataObject1::TestDataObject1(DataContext* context) : DataObject(context)
{
}

TestDataObject1::~TestDataObject1()
{
}
