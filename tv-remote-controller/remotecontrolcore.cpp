#include "remotecontrolcore.h"

#include "messagehandler.h"
#include "settingshandler.h"
#include "socketutils.h"

// RemoteControlCore class constructor
// Creating signal conctions and checking for previous paired devicee
RemoteControlCore::RemoteControlCore(QObject *parent) : QObject(parent)
{
    connect(&upnp_discovery_, &UpnpDiscovery::FoundDialDevice, this, &RemoteControlCore::DialDeviceDetected);
    connect(&pairing_handler_, &PairingHandler::PairingFinished, this, &RemoteControlCore::onPairingFinished);
    connect(&pairing_handler_, &PairingHandler::EnterPairingCode, this, &RemoteControlCore::enterPairingCode);
    upnp_discovery_.StartDiscovery(); //remove
    if (Settings::SettingsHandler::GetInstance()->GetLastDeviceName() != "") {
        command_sender_.StartSending("test", Settings::SettingsHandler::GetInstance()->GetLastDeviceIp(), "key.pem", "cert.pem");
    }

}

// This function is a bridge to recieve pairing key input from QML ui and pass it to
// pairing handler class
// param pairing_code: QString entered pairing code
void RemoteControlCore::setPairingKey(const QString &pairing_code)
{
    pairing_handler_.FinishPairing(pairing_code);
}

// This function is a bridge to receive key codes from QML ui and pass them to
// command sender class
// param key: integer of entered key code
void RemoteControlCore::sendKey(const int &key)
{
    command_sender_.SendKey(key);
}

// This function will provide device model for gui access
// return: DeviceModel* of available devices
DeviceModel* RemoteControlCore::getDeviceModel()
{
    return &device_model_;
}

// This function will receive target device information to start pairing process
// param device_name: const QString& of target device name
// param device_ip: const QString& of target device ip
void RemoteControlCore::pairDevice(const QString& device_name, const QString& device_ip)
{
    DialDevice dial_device;
    dial_device.dial_rest_url.setHost(device_ip);
    dial_device.friendly_name = device_name;
    device_ = dial_device;
    // creating public key and certificate of client
    CreatePrivateKeyAndCertificate("key.pem", "cert.pem");
    // start pairing process
    pairing_handler_.StartPairing("hmi", device_.dial_rest_url.host(), "key.pem", "cert.pem");
}

// This function will return the last paired device name
// return: QString of last paired device name
QString RemoteControlCore::getDeviceName()
{
    return Settings::SettingsHandler::GetInstance()->GetLastDeviceName();
}

// This function is a callback for detected dial device.
// After detcection of device it will add found device to the device model
// param dial_rest_url: QUrl of rest dial address
// param device_description: QByteArray of raw dial device information in xml format
void RemoteControlCore::DialDeviceDetected(const QUrl &dial_rest_url, const QByteArray &device_description)
{
    device_ = MessageHandler::ParseDialDeviceDescription(dial_rest_url, device_description);
    qDebug()<<"name = "<<device_.friendly_name;
    qDebug()<<"ip = "<<device_.dial_rest_url.host();

    DeviceInfo device_info(device_model_.rowCount(), device_.friendly_name, device_.dial_rest_url.host());
    device_model_.addDevice(device_info);
//    CreatePrivateKeyAndCertificate("key.pem", "cert.pem");
//    pairing_handler_.StartPairing("hmi", device_.dial_rest_url.host(), "key.pem", "cert.pem");

}

// This function is a callback for finished pairing signal.
// It will save the paired device information in settings and start sending keys socket
void RemoteControlCore::onPairingFinished()
{
    Settings::SettingsHandler::GetInstance()->SetLastDeviceName(device_.friendly_name);
    Settings::SettingsHandler::GetInstance()->SetLastDeviceIp(device_.dial_rest_url.host());
    emit deviceNameChanged(device_.friendly_name);
    command_sender_.StartSending("test", Settings::SettingsHandler::GetInstance()->GetLastDeviceIp(), "key.pem", "cert.pem");
}
