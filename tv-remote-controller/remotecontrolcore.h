#ifndef REMOTECONTROLCORE_H
#define REMOTECONTROLCORE_H

#include <QObject>
#include "messagehandler.h"
#include "upnpdiscovery.h"
#include "pairinghandler.h"

class RemoteControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlCore(QObject *parent = nullptr);

signals:

private slots:
    void DialDeviceDetected(const QUrl& dial_rest_url, const QByteArray& device_description);

private:
    void Start();
    UpnpDiscovery upnp_discovery_;
    PairingHandler pairing_handler_;

};

#endif // REMOTECONTROLCORE_H
