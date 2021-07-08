#ifndef SETTINGSHANDLERTESTCASE_H
#define SETTINGSHANDLERTESTCASE_H

#include <QObject>

class SettingsHandlerTestCase: public QObject
{
    Q_OBJECT

public:
    SettingsHandlerTestCase();
private slots:
    void SettingsHandlerGetLastDeviceNameTestDefault();
    void SettingsHandlerGetLastDeviceNameTest();
    void SettingsHandlerGetLastDeviceIpTestDefault();
    void SettingsHandlerGetLastDeviceIpTest();
};

#endif // SETTINGSHANDLERTESTCASE_H
