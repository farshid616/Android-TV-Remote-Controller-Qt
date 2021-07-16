#ifndef KEYCOMMANDSENDER_H
#define KEYCOMMANDSENDER_H

#include <QObject>
#include <QtNetwork>

// This class is responsible to handle send keys process
class KeyCommandSender : public QObject
{
    Q_OBJECT
public:
    explicit KeyCommandSender(QObject *parent = nullptr);
    void StartSending(const QString& device_name, const QString& server_ip,
                      const QString& private_key_path, const QString& certificate_path);
    void SendKey(const int& key_code);

signals:
private slots:
    void SocketDataReadyRead();
    void SslErrors(const QList<QSslError>& errors);
private:
    void SendData(const QByteArray& data);
    static void MessageParser(const QByteArray& raw_data);
    QSslSocket* sending_socket_ = nullptr;
    QString device_name_{};
};

#endif // KEYCOMMANDSENDER_H
