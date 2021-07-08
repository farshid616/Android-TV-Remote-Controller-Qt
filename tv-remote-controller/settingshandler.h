#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QString>
#include <memory>
#include <QSettings>

namespace Settings  {

const QString SETTINGS_FILE_NAME = "settings.ini";
const QString DEVICE_NAME = "DEVICE_NAME";
const QString DEVICE_IP = "DEVICE_IP";

class SettingsHandler
{
public:
//    std::shared_ptr<SettingsHandler> GetInstance();
    static SettingsHandler* GetInstance();
    QString GetDeviceName() const;
    void SetDeviceName(const QString& device_name);
    QString GetDeviceIp() const;
    void SetDeviceIp(const QString& device_ip);

private:
    SettingsHandler();
    QSettings* settings_;
};

}

#endif // SETTINGSHANDLER_H
