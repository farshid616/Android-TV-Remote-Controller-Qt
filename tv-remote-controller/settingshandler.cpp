#include "settingshandler.h"

Settings::SettingsHandler::~SettingsHandler() {
    delete settings_;
}

Settings::SettingsHandler::SettingsHandler()
{
    settings_ = new QSettings(SETTINGS_FILE_NAME, QSettings::IniFormat);
}

Settings::SettingsHandler *Settings::SettingsHandler::GetInstance()
{
    static SettingsHandler instance;
    return &instance;
}

QString Settings::SettingsHandler::GetLastDeviceName() const
{
    return settings_->value(LAST_DEVICE_NAME, "").toString();
}

void Settings::SettingsHandler::SetLastDeviceName(const QString &device_name)
{
    settings_->setValue(LAST_DEVICE_NAME, device_name);
}

QString Settings::SettingsHandler::GetLastDeviceIp() const
{
    return settings_->value(LAST_DEVICE_IP, "").toString();
}

void Settings::SettingsHandler::SetLastDeviceIp(const QString &device_ip)
{
    settings_->setValue(LAST_DEVICE_IP, device_ip);
}
