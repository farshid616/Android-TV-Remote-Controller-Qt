#ifndef REMOTECONTROLCORE_H
#define REMOTECONTROLCORE_H

#include <QObject>
#include "messagehandler.h"
#include "upnpdiscovery.h"

class RemoteControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlCore(QObject *parent = nullptr);

signals:

private slots:
    void DialDeviceDetected(const QUrl& dial_rest_url, const QByteArray& device_description);

private:
    UpnpDiscovery upnp_discovery_;

};

#endif // REMOTECONTROLCORE_H
