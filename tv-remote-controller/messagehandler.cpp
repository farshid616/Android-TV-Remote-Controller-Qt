#include "messagehandler.h"

#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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

QByteArray MessageHandler::CreatePairingRequestJsonMessage(const QString &client_name)
{
//    message = {"protocol_version":1,"payload":{"service_name":"androidtvremote","client_name":client_name},"type":10,"status":200}
    QJsonObject jobject, payload_object;
    payload_object["service_name"] = "androidtvremote";
    payload_object["client_name"] = client_name;

    jobject["protocol_version"] = 1;
    jobject["type"] = 10;
    jobject["status"] = 200;
    jobject["payload"] = payload_object;
    QJsonDocument json_document(jobject);
    return json_document.toJson();
}

QByteArray MessageHandler::CreateOptionJsonMessage()
{
//    message = {"protocol_version":1,"payload":{"output_encodings":[{"symbol_length":4,"type":3}],
//    "input_encodings":[{"symbol_length":4,"type":3}],"preferred_role":1},"type":20,"status":200}
      QJsonObject jobject, payload_object, output_encoding, input_encoding;
      QJsonArray input_encoding_array, output_encoding_array;
      output_encoding["symbol_length"] = 4;
      output_encoding["type"] = 3;
      input_encoding["symbol_length"] = 4;
      input_encoding["type"] = 3;
      input_encoding_array.push_back(input_encoding);
      output_encoding_array.push_back(output_encoding);

      payload_object["input_encodings"] = input_encoding_array;
      payload_object["output_encodings"] = output_encoding_array;
      payload_object["preferred_role"] = 1;

      jobject["protocol_version"] = 1;
      jobject["type"] = 20;
      jobject["status"] = 200;
      jobject["payload"] = payload_object;
      QJsonDocument json_document(jobject);
      return json_document.toJson();
}

QByteArray MessageHandler::CreateConfigurationJsonMessage()
{
//    message = {"protocol_version":1,"payload":{"encoding":{"symbol_length":4,"type":3},"client_role":1},"type":30,"status":200}
    QJsonObject jobject, payload_object, encoding_object;
    encoding_object["symbol_length"] = 4;
    encoding_object["type"] = 3;

    payload_object["client_role"] = 1;
    payload_object["encoding"] = encoding_object;

    jobject["protocol_version"] = 1;
    jobject["type"] = 30;
    jobject["status"] = 200;
    jobject["payload"] = payload_object;
    QJsonDocument json_document(jobject);
    return json_document.toJson();
}

QByteArray MessageHandler::CreateSecretJsonMessage(const QString &secret_hash)
{
//    message = {"protocol_version":1,"payload":{"secret":base64.b64encode(secret_hash).decode()},"type":40,"status":200}
    QJsonObject jobject, payload_object;
    payload_object["secret"] = secret_hash;

    jobject["protocol_version"] = 1;
    jobject["type"] = 40;
    jobject["status"] = 200;
    jobject["payload"] = payload_object;
    QJsonDocument json_document(jobject);
    return json_document.toJson();
}

bool MessageHandler::JsonMessageParser(const QByteArray &json_message, int &status, int &type)
{
    QJsonParseError parser_error{};
    QJsonDocument documet = QJsonDocument::fromJson(json_message, &parser_error);
    QJsonObject json_object = documet.object();

    if(parser_error.error != QJsonParseError::NoError)
        return false;

    status = json_object["status"].toInt();
    type = json_object["type"].toInt();
    return true;
}
