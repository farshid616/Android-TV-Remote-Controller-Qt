#include <QtTest>

#include "settingshandler.h"
// add necessary includes here

class TestCase : public QObject
{
    Q_OBJECT

public:
    TestCase();
//    ~TestCase();

private slots:
    void SettingsHandlerGetDeviceNameTestDefault();
    void SettingsHandlerGetDeviceNameTest();
    void SettingsHandlerGetDeviceIpTestDefault();
    void SettingsHandlerGetDeviceIpTest();

};

TestCase::TestCase()
{

}

void TestCase::SettingsHandlerGetDeviceNameTestDefault()
{
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetDeviceName() == "");
}

//TestCase::~TestCase()
//{

//}

void TestCase::SettingsHandlerGetDeviceNameTest()
{
    Settings::SettingsHandler::GetInstance()->SetDeviceName("test");
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetDeviceName() == "test");
}

void TestCase::SettingsHandlerGetDeviceIpTestDefault()
{
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetDeviceIp() == "");
}

void TestCase::SettingsHandlerGetDeviceIpTest()
{
    Settings::SettingsHandler::GetInstance()->SetDeviceIp("192.168.0.144");
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetDeviceIp() == "192.168.0.144");
}

QTEST_APPLESS_MAIN(TestCase)

#include "tst_testcase.moc"
