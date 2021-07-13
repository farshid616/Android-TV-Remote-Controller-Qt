#ifndef MESSAGEHANDLERTESTCASE_H
#define MESSAGEHANDLERTESTCASE_H

#include <QObject>

class MessageHandlerTestCase : public QObject
{
    Q_OBJECT
public:
    MessageHandlerTestCase();

private slots:
    void DialDeviceDescriptionParserTest();
    void DialDeviceDescriptionParserTestInvalid();
    void CreatePairingJsonMessageTest();
    void CreateOptionJsonMessageTest();
    void CreateConfigurationJsonMessageTest();
    void CreateSecretJsonMessageTest();
    void JsonMessageParserTest();
    void JsonMessageParserTestInvalid();
    void ProtoBufConfigurationMessageCreatorTest();
    void ProtoBufSendKeyMessageCreatorTest();
    void ProtoBufSendKeyMessageCreatorTestRelease();

};

#endif // MESSAGEHANDLERTESTCASE_H
