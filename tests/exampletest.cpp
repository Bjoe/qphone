
#include <QtTest/QtTest>

#include "testconfig.h"

class ExampleTest : public QObject
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
