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

};

#endif // MESSAGEHANDLERTESTCASE_H
