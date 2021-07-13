#ifndef PAIRINGHANDLER_H
#define PAIRINGHANDLER_H

#include <QObject>
#include <QtNetwork>

class PairingHandler : public QObject
{
    Q_OBJECT
public:
    explicit PairingHandler(QObject* parent = nullptr);
    void StartPairing(const QString& client_name, const QString& server_ip,
                      const QString& private_key_path, const QString& certificate_path);

signals:
    void PairingFinished();
private slots:
    void SocketDataReadyRead();
    void SslErrors(const QList<QSslError>& errors);
private:
    void SendData(const QByteArray& data);
    void ParsePairingData(const QByteArray &data);
    QByteArray GetBase64SecretHash();
    QSslSocket* pairing_socket_ = nullptr;
};

#endif // PAIRINGHANDLER_H
