#include "settingshandler.h"

// Distructor of SettingsHandler
Settings::SettingsHandler::~SettingsHandler() {
    delete settings_;
}

// Constructor of SettingsHandler
Settings::SettingsHandler::SettingsHandler()
{
    settings_ = new QSettings(SETTINGS_FILE_NAME, QSettings::IniFormat);
}

// This function will return the only instance of class
// return: instance of SettingsHandler singleton class
Settings::SettingsHandler *Settings::SettingsHandler::GetInstance()
{
    static SettingsHandler instance;
    return &instance;
}

// This function will return the stored device name
// return: QString of stored last pairing device name
QString Settings::SettingsHandler::GetLastDeviceName() const
{
    return settings_->value(LAST_DEVICE_NAME, "").toString();
}

// This function will return the stored device name
// return: QString of stored last pairing device name
void Settings::SettingsHandler::SetLastDeviceName(const QString &device_name)
{
    settings_->setValue(LAST_DEVICE_NAME, device_name);
}

// This function will return the stored device ip
// return: QString of stored last pairing device ip
QString Settings::SettingsHandler::GetLastDeviceIp() const
{
    return settings_->value(LAST_DEVICE_IP, "").toString();
}

// This function will return the stored device ip
// return: QString of stored last pairing device ip
void Settings::SettingsHandler::SetLastDeviceIp(const QString &device_ip)
{
    settings_->setValue(LAST_DEVICE_IP, device_ip);
}
