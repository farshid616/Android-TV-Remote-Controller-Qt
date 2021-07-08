#include "settingshandlertestcase.h"

#include <QTest>
#include "settingshandler.h"

SettingsHandlerTestCase::SettingsHandlerTestCase()
{

}

void SettingsHandlerTestCase::SettingsHandlerGetLastDeviceNameTestDefault()
{
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetLastDeviceName() == "");
}

void SettingsHandlerTestCase::SettingsHandlerGetLastDeviceNameTest()
{
    Settings::SettingsHandler::GetInstance()->SetLastDeviceName("test");
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetLastDeviceName() == "test");
}

void SettingsHandlerTestCase::SettingsHandlerGetLastDeviceIpTestDefault()
{
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetLastDeviceIp() == "");
}

void SettingsHandlerTestCase::SettingsHandlerGetLastDeviceIpTest()
{
    Settings::SettingsHandler::GetInstance()->SetLastDeviceIp("192.168.0.144");
    QVERIFY(Settings::SettingsHandler::GetInstance()->GetLastDeviceIp() == "192.168.0.144");
}
