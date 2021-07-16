#include "pairinghandler.h"

#include "socketutils.h"
#include "messagehandler.h"

// PairingHandler class constructor
// Creating QsslSocket object and connecting its signals
PairingHandler::PairingHandler(QObject *parent) : QObject(parent)
{
    pairing_socket_ = new QSslSocket(this);

    connect(pairing_socket_, &QSslSocket::readyRead,
            this, &PairingHandler::SocketDataReadyRead);
    connect(pairing_socket_, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors),
            this, &PairingHandler::SslErrors);
}

// This function will initializing the ssl socket by setting the PrivateKey, Certificate
// and connecting the socket to device ip and port
// param device_name: QString of android device name
// param server_ip: QString of android device ip
// param private_key_path: QString path to private key pem file, includeing name of the file and extention
// param certificate_path: QString path to certificate pem file, includeing name of the file and extention
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

// This function will create the last message of pairing by recieving the entered 4 digit pairing code
// param pairing_code: QString of entered 4 digit pairing code
void PairingHandler::FinishPairing(const QString &pairing_code)
{
    SendData(MessageHandler::CreateSecretJsonMessage(QString(GetBase64SecretHash(pairing_code))));
}

// This function is a callback for socket to receive incoming data
// after receiving data it will passed to the message parser
void PairingHandler::SocketDataReadyRead()
{
    QByteArray data{};

    data = pairing_socket_->readAll();

    if (data.size() > 4) {
        ParsePairingData(data);
    }
}

// This is a callback function for handling ssl errors
// param errors: list of occured ssl errors
void PairingHandler::SslErrors(const QList<QSslError> &errors)
{
    for (const auto& item: errors)
        qDebug()<<"error = "<<item;
}

// This function is responsible to write given bytes on socket
// param data: QByteArray of data
void PairingHandler::SendData(const QByteArray &data)
{
    // At first we should send, size of the data seperately
    pairing_socket_->write(GetFourByteArray(QString(data).size()));
    pairing_socket_->write(data);
}

// ParsePairingData receives raw data and will parse the data to find message type and status
// to response to it correctly
// param data: QByteArray of received socket raw data
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
                emit EnterPairingCode();
                qDebug()<<"enter ";
            } else if (type == 41) {
                emit PairingFinished();
            }
        } else {
            qDebug()<<"status error";
        }
    } else {
        qDebug()<<"parse error";
    }
}

// This function will receive 4 digit entered pairing code and create a SHA-256 secret message consisting of:
// client modulus, client exponent, server modulus, server exponent and last 2 digit of entered key
// param pairing_code: QString 4 digit entered pairing code
// return: QByteArray of based64 encoded created hash
QByteArray PairingHandler::GetBase64SecretHash(const QString &pairing_code)
{
    // Regex to extracting modulus and exponent from certificate
    const QRegularExpression expression(QLatin1String(R"(Public-Key:[.\s\S]+Modulus:([.\s\S]+)Exponent:(.+))"), QRegularExpression::MultilineOption);
    const QRegularExpressionMatch client_regex_match(expression.match(pairing_socket_->localCertificate().toText()));
    const QRegularExpressionMatch server_regex_match(expression.match(pairing_socket_->peerCertificate().toText()));

    QCryptographicHash secret_hash(QCryptographicHash::Sha256);
    QString code_in;
    QStringList exponent = QString("01:00:01").split(':');

    QByteArray client_mod, client_exp, server_mod, server_exp;

    code_in = pairing_code.section("",3);

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
