#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "datamodel.h"

class MessageHandler
{
public:
    MessageHandler() = default;
    static DialDevice ParseDialDeviceDescription(const QUrl& dial_rest_url, const QByteArray& device_description);
    static QByteArray CreatePairingRequestJsonMessage(const QString& client_name);
    static QByteArray CreateOptionJsonMessage();
    static QByteArray CreateConfigurationJsonMessage();
    static QByteArray CreateSecretJsonMessage(const QString& secret_hash);
    static bool JsonMessageParser(const QByteArray& json_message, int& status, int& type);
};

#endif // MESSAGEHANDLER_H
