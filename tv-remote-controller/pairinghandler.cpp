#include "pairinghandler.h"

#include <iostream>
#include "socketutils.h"
#include "messagehandler.h"

PairingHandler::PairingHandler(QObject *parent) : QObject(parent)
{
    pairing_socket_ = new QSslSocket(this);

    connect(pairing_socket_, &QSslSocket::readyRead,
            this, &PairingHandler::SocketDataReadyRead);
    connect(pairing_socket_, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
            this, &PairingHandler::SslErrors);
}

void PairingHandler::StartPairing(const QString &client_name, const QString &server_ip,
                                  const QString& private_key_path, const QString& certificate_path)
{
    if (pairing_socket_->isOpen())
        pairing_socket_->close();

    pairing_socket_->setLocalCertificate(certificate_path);
    pairing_socket_->setPrivateKey(private_key_path);
    pairing_socket_->setPeerVerifyMode(QSslSocket::QueryPeer);
    pairing_socket_->connectToHostEncrypted(server_ip, 6467);

    SendData(MessageHandler::CreatePairingRequestJsonMessage(client_name));
}

void PairingHandler::SocketDataReadyRead()
{
    QByteArray data{};

    data = pairing_socket_->readAll();

    if (data.size() > 4) {
        ParsePairingData(data);
    }
}

void PairingHandler::SslErrors(const QList<QSslError> &errors)
{
    for (const auto& item: errors)
        qDebug()<<"error = "<<item;
}

void PairingHandler::SendData(const QByteArray &data)
{
    pairing_socket_->write(GetFourByteArray(QString(data).size()));
    pairing_socket_->write(data);
}

void PairingHandler::ParsePairingData(const QByteArray &data)
{
    int type{}, status{};
    if (MessageHandler::JsonMessageParser(data, status, type)) {
        if( status == 200) {
            if( type == 11) {
                SendData(MessageHandler::CreateOptionJsonMessage());
            } else if (type == 20) {
                SendData(MessageHandler::CreateConfigurationJsonMessage());
            } else if (type == 31) {
                SendData(MessageHandler::CreateSecretJsonMessage(QString(GetBase64SecretHash())));
            }
        } else {
            qDebug()<<"status else";
        }
    } else {
        qDebug()<<"parse error";
    }
}

QByteArray PairingHandler::GetBase64SecretHash()
{
    const QRegularExpression expression(QLatin1String(R"(Public-Key:[.\s\S]+Modulus:([.\s\S]+)Exponent:(.+))"), QRegularExpression::MultilineOption);
    const QRegularExpressionMatch client_regex_match(expression.match(pairing_socket_->localCertificate().toText()));
    const QRegularExpressionMatch server_regex_match(expression.match(pairing_socket_->peerCertificate().toText()));

    QCryptographicHash secret_hash(QCryptographicHash::Sha256);
    QString code_in;
    std::string in;
    QStringList exponent = QString("01:00:01").split(':');

    QByteArray client_mod, client_exp, server_mod, server_exp;
    //TODO: Temporary should change
    std::cout<<"enter : \n";
    std::cin>>in;
    // Temporary End
    code_in = in.c_str();
    code_in = code_in.section("",3);

    for (const auto& item: exponent) {
        client_exp.append(QByteArray::fromHex(item.toLocal8Bit()));
        server_exp.append(QByteArray::fromHex(item.toLocal8Bit()));
    }

    if (client_regex_match.hasMatch()) {

        QStringList mod = (QString("%1").arg((client_regex_match.captured(1).replace(" ","").replace("\n","")))).split(':');
        mod.removeAt(0);
        for (const auto& item: mod) {
            client_mod.append(QByteArray::fromHex(item.toLocal8Bit()));
        }
    }

    if (server_regex_match.hasMatch()) {

        QStringList mod = (QString("%1").arg((server_regex_match.captured(1).replace(" ","").replace("\n","")))).split(':');
        mod.removeAt(0);
        for (const auto& item: mod) {
            server_mod.append(QByteArray::fromHex(item.toLocal8Bit()));
        }

    }

    secret_hash.addData(client_mod);
    secret_hash.addData(client_exp);
    secret_hash.addData(server_mod);
    secret_hash.addData(server_exp);
    secret_hash.addData(QByteArray::fromHex(code_in.toLocal8Bit()));
    return secret_hash.result().toBase64();

}
