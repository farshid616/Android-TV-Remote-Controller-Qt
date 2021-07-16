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
    if (Settings::SettingsHandler::GetInstance()->GetLastDeviceName() == "") {
        upnp_discovery_.StartDiscovery();
    } else {
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

// This function will return the last paired device name
// return: QString of last paired device name
QString RemoteControlCore::getDeviceName()
{
    return Settings::SettingsHandler::GetInstance()->GetLastDeviceName();
}

// This function is a callback for detected dial device.
// After detcection of device it will generate certificate and start the pairing process
// param dial_rest_url: QUrl of rest dial address
// param device_description: QByteArray of raw dial device information in xml format
void RemoteControlCore::DialDeviceDetected(const QUrl &dial_rest_url, const QByteArray &device_description)
{
    device_ = MessageHandler::ParseDialDeviceDescription(dial_rest_url, device_description);
    qDebug()<<"name = "<<device_.friendly_name;
    qDebug()<<"ip = "<<device_.dial_rest_url.host();

    CreatePrivateKeyAndCertificate("key.pem", "cert.pem");
    pairing_handler_.StartPairing("hmi", device_.dial_rest_url.host(), "key.pem", "cert.pem");

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
