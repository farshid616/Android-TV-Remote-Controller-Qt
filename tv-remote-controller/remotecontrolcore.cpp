#include "remotecontrolcore.h"

#include "messagehandler.h"
#include "socketutils.h"

RemoteControlCore::RemoteControlCore(QObject *parent) : QObject(parent)
{
//    CreatePrivateKeyAndCertificate("key.pem", "cert.pem");
    connect(&upnp_discovery_, &UpnpDiscovery::FoundDialDevice, this, &RemoteControlCore::DialDeviceDetected);
    upnp_discovery_.StartDiscovery();

}

void RemoteControlCore::DialDeviceDetected(const QUrl &dial_rest_url, const QByteArray &device_description)
{
    DialDevice device = MessageHandler::ParseDialDeviceDescription(dial_rest_url, device_description);
    qDebug()<<"name = "<<device.friendly_name;
    qDebug()<<"ip = "<<device.dial_rest_url.host();

//    pairing_handler_.StartPairing("hmi", device.dial_rest_url.host(), "key.pem", "cert.pem");

//    QTimer::singleShot(15000, [=]{
//            command_sender_.StartSending(device.friendly_name, device.dial_rest_url.host(), "key.pem", "cert.pem");
//            qDebug()<<"connect";
//        });
    command_sender_.StartSending("test", device.dial_rest_url.host(), "key.pem", "cert.pem");
    QTimer::singleShot(5000, [=]{
            command_sender_.SendKey(24);
            qDebug()<<"send key";
        });
    QTimer::singleShot(6000, [=]{
            command_sender_.SendKey(25);
            qDebug()<<"send key";
        });
    QTimer::singleShot(7000, [=]{
            command_sender_.SendKey(19);
            qDebug()<<"send key";
        });

}

void RemoteControlCore::Start()
{
    pairing_handler_.StartPairing("hmi", "192.168.0.144", "key.pem", "cert.pem");
}
