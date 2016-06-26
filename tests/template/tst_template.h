#ifndef TST_TEMPLATE_H
#define TST_TEMPLATE_H

#include <QtCore>
#include <QtTest>

using namespace ralph::templ;

class TemplateTests : public QObject
{
    Q_OBJECT

public:
    TemplateTests();

private:

private Q_SLOTS:
    void templateTest();

public slots:
};

#endif // TST_TEMPLATE_H
