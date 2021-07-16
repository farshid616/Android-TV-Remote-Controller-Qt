#include "keycommandsender.h"

#include <iostream>
#include "messagehandler.h"

// KeyCommandSender class constructor
// Creating QsslSocket object and connecting its signals
KeyCommandSender::KeyCommandSender(QObject *parent) : QObject(parent)
{
    sending_socket_ = new QSslSocket(this);

    connect(sending_socket_, &QSslSocket::readyRead,
            this, &KeyCommandSender::SocketDataReadyRead);
    connect(sending_socket_, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
            this, &KeyCommandSender::SslErrors);
}

// This function will initializing the ssl socket by setting the PrivateKey, Certificate
// and connecting the socket to device ip and port
// param device_name: QString of android device name
// param server_ip: QString of android device ip
// param private_key_path: QString path to private key pem file, includeing name of the file and extention
// param certificate_path: QString path to certificate pem file, includeing name of the file and extention
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

// This function recives a remote key code and prepare commands and send them
// to SendData function
// param key_code: integer of remote key code that exist in the key code enumeration
void KeyCommandSender::SendKey(const int &key_code)
{
    SendData(MessageHandler::ProtoBufConfigurationMessageCreator(device_name_));
    SendData(MessageHandler::ProtoBufSendKeyMessageCreator(key_code));
    SendData(MessageHandler::ProtoBufSendKeyMessageCreator(key_code, true, 1));
}

// This function is a callback for socket to receive incoming data
// after receiving data it will passed to the message parser
void KeyCommandSender::SocketDataReadyRead()
{
    QByteArray data{};

    data = sending_socket_->readAll();
    MessageParser(data);
}

// This is a callback function for handling ssl errors
// param errors: list of occured ssl errors
void KeyCommandSender::SslErrors(const QList<QSslError> &errors)
{
    for (const auto& item: errors)
        qDebug()<<"error = "<<item;
}

// This function is responsible to write given bytes on socket
// param data: QByteArray of data
void KeyCommandSender::SendData(const QByteArray &data)
{
    sending_socket_->write(data);
}

// MessageParser receives raw data and will parse the data to find message type
// param raw_data: QByteArray of received socket raw data
void KeyCommandSender::MessageParser(const QByteArray &raw_data)
{
    std::vector<int> message{};
    std::transform(raw_data.begin(), raw_data.end(), std::back_inserter(message),
                   [](char item) -> int{ return int(item);});

    if (message.size() > 2) {
        if (message[1] == 7) {
            //confirmation ack
            qDebug()<<"Confirm Ack";
        } else if (message[1] == 20) {
            //ping
            qDebug()<<"Ping";
        } else if (message[1] == 27 || message[1] == 38) {
            //info message
            qDebug()<<"info Message";
        }
    }
}
