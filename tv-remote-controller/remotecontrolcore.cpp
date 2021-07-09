#include "remotecontrolcore.h"

RemoteControlCore::RemoteControlCore(QObject *parent) : QObject(parent)
{
    connect(&upnp_discovery_, &UpnpDiscovery::FoundDialDevice, this, &RemoteControlCore::DialDeviceDetected);
    upnp_discovery_.StartDiscovery();
}

void RemoteControlCore::DialDeviceDetected(const QUrl &dial_rest_url, const QByteArray &device_description)
{
    DialDevice device = MessageHandler::ParseDialDeviceDescription(dial_rest_url, device_description);
    qDebug()<<"name = "<<device.friendly_name;
    qDebug()<<"ip = "<<device.dial_rest_url.host();


}
