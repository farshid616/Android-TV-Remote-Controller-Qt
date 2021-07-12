#include "upnpdiscovery.h"

UpnpDiscovery::UpnpDiscovery(QObject *parent) : QObject(parent)
{
    discovery_state_ = StateIdle;
    network_access_manager_ = new QNetworkAccessManager(this);
    udp_socket_ = new QUdpSocket(this);

    connect(udp_socket_, &QUdpSocket::readyRead, this, &UpnpDiscovery::ProcessDiscoveryData);
    connect(network_access_manager_, &QNetworkAccessManager::finished, this, &UpnpDiscovery::ProcessDeviceDescription);

}

void UpnpDiscovery::StartDiscovery()
{
    if (discovery_state_ != StateIdle) {
        qDebug() << "Not Idle";
        return;
    }

    discovery_state_ = StateSearching;

    bool ok = udp_socket_->bind(QHostAddress(QHostAddress::AnyIPv4));

    if (!ok) {
        qDebug() << "Bind failed" << udp_socket_->errorString();
        discovery_state_ = StateError;
        return;
    }

    // Send UPNP Search
    QHostAddress groupAddress("239.255.255.250");
    ok = udp_socket_->joinMulticastGroup(groupAddress);
    if (!ok) {
        qDebug() << "Joining group failed" << udp_socket_->errorString();
        discovery_state_ = StateError;
        return;
    }

    QByteArray message("M-SEARCH * HTTP/1.1\r\n"        \
                       "HOST: 239.255.255.250:1900\r\n" \
                       "MAN: \"ssdp:discover\"\r\n" \
                       "MX: 1\r\n" \
                       "ST: urn:dial-multiscreen-org:service:dial:1\r\n" \
                       "\r\n");

    ok = udp_socket_->writeDatagram(message.constData(), message.size(),
                                groupAddress, UPNP_PORT);
    if (!ok) {
        qDebug() << "Sending failed" << udp_socket_->errorString();
        discovery_state_ = StateError;
        return;
    }
}

void UpnpDiscovery::ProcessDiscoveryData()
{
    while (udp_socket_->hasPendingDatagrams()) {
        QByteArray reply;
        reply.resize(udp_socket_->pendingDatagramSize());
        udp_socket_->readDatagram(reply.data(), reply.size());

        QList<QByteArray> lines = reply.split('\n');

        if (!lines.empty() && qstrnicmp(lines[0].constData(), "http/1.1 200", 12)) {
            qDebug() << "Unexpected response";
            continue;
        }

        foreach (const QByteArray &line, lines) {
            if (!qstrnicmp(line.constData(), "Location: ", 10)) {
                QByteArray urldata(line.mid(10).trimmed());
                qDebug() << "URL:" << urldata;

                QUrl url(QUrl::fromEncoded(urldata));
                if (!url.isValid()) {
                    qDebug() << "Failed to parse url";
                    continue;
                }

                RequestDeviceDescription(url);
            }
        }
    }
}

void UpnpDiscovery::ProcessDeviceDescription(QNetworkReply *reply)
{

    QByteArray description = reply->readAll();

    QByteArray urlData = reply->rawHeader(QByteArrayLiteral("Application-URL"));

    QUrl dialRestUrl(QUrl::fromEncoded(urlData));

    emit FoundDialDevice(dialRestUrl, description);

    reply->deleteLater();
}

void UpnpDiscovery::RequestDeviceDescription(const QUrl &device_url)
{
    qDebug() << "read device description" << device_url;

    if (!network_access_manager_) {
        qDebug() << "No network access manager";
        return;
    }

    network_access_manager_->get(QNetworkRequest(device_url));

}



