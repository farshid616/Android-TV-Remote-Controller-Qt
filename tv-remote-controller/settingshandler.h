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
    ~SettingsHandler();
    //Deleting copy constructor to preventing singleton from copy
    SettingsHandler(const SettingsHandler&) = delete;
    //Deleting move constructor to preventing singleton from move
    SettingsHandler(SettingsHandler&&) = delete;
    //Deleting copy assignment operator to preventing singleton from assignment
    SettingsHandler& operator=(const SettingsHandler&) = delete;
    //Deleting move assignment operator to preventing singleton from move assignment
    SettingsHandler& operator=(SettingsHandler&&) = delete;

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
