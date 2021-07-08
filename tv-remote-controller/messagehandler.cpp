#include "messagehandler.h"

#include <QXmlStreamReader>
#include <memory>
#include <QDebug>

MessageHandler::MessageHandler()
{

}

DialDevice MessageHandler::ParseDialDeviceDescription(const QUrl &dial_rest_url, const QByteArray &device_description)
{
    DialDevice device;
    device.dial_rest_url = dial_rest_url;

    // Parse description
    QXmlStreamReader xml(device_description);
    while(!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            QStringRef name(xml.name());

            if (name == QLatin1String("friendlyName")) {
                device.friendly_name = xml.readElementText();
            }
            else if (name == QLatin1String("modelName")) {
                device.model_name = xml.readElementText();
            }
            else if (name == QLatin1String("manufacturer")) {
                device.manufacturer_name = xml.readElementText();
            }
            else if (name == QLatin1String("deviceType")) {
                device.type = xml.readElementText();
            }
            else if (name == QLatin1String("UDN")) {
                device.udn = xml.readElementText();
            }
        }
    }

    if (xml.hasError()) {
        qDebug() << "Unable to parse description" << xml.errorString() << xml.lineNumber();
    }
    return device;
}
