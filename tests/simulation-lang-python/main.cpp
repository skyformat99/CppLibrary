#include "tst_template.h"

int main()
{
    TemplateTests tst_Template;

    QTest::qExec(&tst_Template);

    return 0;
}
