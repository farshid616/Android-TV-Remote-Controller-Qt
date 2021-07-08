#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "datamodel.h"

class MessageHandler
{
public:
    MessageHandler();
    static DialDevice ParseDialDeviceDescription(const QUrl& dial_rest_url, const QByteArray& device_description);

};

#endif // MESSAGEHANDLER_H
