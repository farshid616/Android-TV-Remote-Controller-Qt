#ifndef UPNPDISCOVERY_H
#define UPNPDISCOVERY_H

#include <QObject>
//#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkAccessManager>
//#include <QNetworkRequest>
#include <QNetworkReply>
#include "datamodel.h"

const int UPNP_PORT = 1900;

class UpnpDiscovery : public QObject
{
    Q_OBJECT
public:
    explicit UpnpDiscovery(QObject *parent = nullptr);
    void StartDiscovery();


signals:
    void FoundDialDevice(QUrl, QByteArray);

private slots:
    void ProcessDiscoveryData();
    void ProcessDeviceDescription(QNetworkReply *reply);


private:
    void RequestDeviceDescription(const QUrl& device_url);
    DiscoveryState discovery_state_;
    QUdpSocket *udp_socket_;
    QNetworkAccessManager *network_access_manager_;
};

#endif // UPNPDISCOVERY_H
