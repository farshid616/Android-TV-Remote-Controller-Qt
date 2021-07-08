#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QString>
#include <memory>
#include <QSettings>

namespace Settings  {

const QString SETTINGS_FILE_NAME = "settings.ini";
const QString LAST_DEVICE_NAME = "LAST_DEVICE_NAME";
const QString LAST_DEVICE_IP = "LAST_DEVICE_IP";

class SettingsHandler
{
public:
    static SettingsHandler* GetInstance();
    QString GetLastDeviceName() const;
    void SetLastDeviceName(const QString& device_name);
    QString GetLastDeviceIp() const;
    void SetLastDeviceIp(const QString& device_ip);

private:
    SettingsHandler();
    QSettings* settings_;
};

}

#endif // SETTINGSHANDLER_H
