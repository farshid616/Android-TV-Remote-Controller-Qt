#include "keycommandsender.h"

#include <iostream>
#include "messagehandler.h"

KeyCommandSender::KeyCommandSender(QObject *parent) : QObject(parent)
{
    sending_socket_ = new QSslSocket(this);

    connect(sending_socket_, &QSslSocket::readyRead,
            this, &KeyCommandSender::SocketDataReadyRead);
    connect(sending_socket_, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
            this, &KeyCommandSender::SslErrors);
}

void KeyCommandSender::StartSending(const QString &device_name, const QString& server_ip,
                                    const QString& private_key_path, const QString& certificate_path)
{
    device_name_ = device_name;
    if (sending_socket_->isOpen())
        sending_socket_->close();

    sending_socket_->setLocalCertificate(certificate_path);
    sending_socket_->setPrivateKey(private_key_path);
    sending_socket_->setPeerVerifyMode(QSslSocket::QueryPeer);
    sending_socket_->connectToHostEncrypted(server_ip, 6466);
}

void KeyCommandSender::SendKey(const int &key_code)
{
    SendData(MessageHandler::ProtoBufConfigurationMessageCreator(device_name_));
    SendData(MessageHandler::ProtoBufSendKeyMessageCreator(key_code));
    SendData(MessageHandler::ProtoBufSendKeyMessageCreator(key_code, true, 1));
}

void KeyCommandSender::SocketDataReadyRead()
{
    QByteArray data{};

    data = sending_socket_->readAll();
    MessageParser(data);
}

void KeyCommandSender::SslErrors(const QList<QSslError> &errors)
{
    for (const auto& item: errors)
        qDebug()<<"error = "<<item;
}

void KeyCommandSender::SendData(const QByteArray &data)
{
    sending_socket_->write(data);
}

void KeyCommandSender::MessageParser(const QByteArray &raw_data)
{
    std::vector<int> message{};
    std::transform(raw_data.begin(), raw_data.end(), std::back_inserter(message),
                   [](char item) -> int{ return int(item);});

    if (message.size() > 2) {
        if (message[1] == 7) {
            //confirmation ack
//            qDebug()<<"Confirm Ack";
        } else if (message[1] == 20) {
            //ping
//            qDebug()<<"Ping";
        } else if (message[1] == 27 || message[1] == 38) {
            //info message
//            qDebug()<<"info Message";
        }
    }
}
