#include "settingshandler.h"



Settings::SettingsHandler::SettingsHandler()
{
    settings_ = new QSettings(SETTINGS_FILE_NAME, QSettings::IniFormat);
}

Settings::SettingsHandler *Settings::SettingsHandler::GetInstance()
{
    static SettingsHandler instance;
    return &instance;
}

QString Settings::SettingsHandler::GetDeviceName() const
{
    return settings_->value(DEVICE_NAME, "").toString();
}

void Settings::SettingsHandler::SetDeviceName(const QString &device_name)
{
    settings_->setValue(DEVICE_NAME, device_name);
}

QString Settings::SettingsHandler::GetDeviceIp() const
{
    return settings_->value(DEVICE_IP, "").toString();
}

void Settings::SettingsHandler::SetDeviceIp(const QString &device_ip)
{
    settings_->setValue(DEVICE_IP, device_ip);
}

//std::shared_ptr<Settings::SettingsHandler> Settings::SettingsHandler::GetInstance()
//{
//    static std::shared_ptr<SettingsHandler> instance = std::make_shared<SettingsHandler> (new QSettings(SETTINGS_FILE_NAME, QSettings::IniFormat));
//    return instance;
//}
