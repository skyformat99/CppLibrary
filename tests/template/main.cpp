int main()
{
    DataObjectTests tst_DataObject;
    SerializerTests tst_Serializer;

    QTest::qExec(&tst_DataObject);
    QTest::qExec(&tst_Serializer);

    return 0;
}
