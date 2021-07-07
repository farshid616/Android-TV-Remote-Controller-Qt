#include <QtTest>

// add necessary includes here

class TestCase : public QObject
{
    Q_OBJECT

public:
    TestCase();
    ~TestCase();

private slots:
    void test_case1();

};

TestCase::TestCase()
{

}

TestCase::~TestCase()
{

}

void TestCase::test_case1()
{

}

QTEST_APPLESS_MAIN(TestCase)

#include "tst_testcase.moc"
