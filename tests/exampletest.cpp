
#include <QtTest/QtTest>

#include "testconfig.h"

#include "testcoverageobject.h"


class ExampleTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testExample();
};

void ExampleTest::initTestCase()
{
}

void ExampleTest::testExample()
{
    QVERIFY(true);
}

QTEST_MAIN(ExampleTest)
#include "moc_exampletest.cpp"
