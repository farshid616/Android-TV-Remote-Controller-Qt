#include "messagehandler.h"

#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <algorithm>

// This function will extract description information of dial response
// param dial_rest_url: QUrl of dial rest address
// param device_description: QByteArray of receive raw data of dial response in xml format
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

// This function will receive name of client and create a json message for pairing request
// param client_name: QString of client name
// return: QByteAray of created json message
QByteArray MessageHandler::CreatePairingRequestJsonMessage(const QString &client_name)
{
    // sample message = {"protocol_version":1,"payload":{"service_name":"androidtvremote","client_name":client_name},"type":10,"status":200}
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

// This function will create a json option message for one of pairing phase
// return: QByteAray of created json message
QByteArray MessageHandler::CreateOptionJsonMessage()
{
      // sample message = {"protocol_version":1,"payload":{"output_encodings":[{"symbol_length":4,"type":3}],
      // "input_encodings":[{"symbol_length":4,"type":3}],"preferred_role":1},"type":20,"status":200}
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

// This function will create a json configuration message for one of pairing phase
// return: QByteAray of created json message
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

// This function will receive generated secret hash and create a json secret message for last step of pairing
// param secret_hash: QString created secret hash
// return: QByteArray of created json message
QByteArray MessageHandler::CreateSecretJsonMessage(const QString &secret_hash)
{
    // message = {"protocol_version":1,"payload":{"secret":base64.b64encode(secret_hash).decode()},"type":40,"status":200}
    QJsonObject jobject, payload_object;
    payload_object["secret"] = secret_hash;

    jobject["protocol_version"] = 1;
    jobject["type"] = 40;
    jobject["status"] = 200;
    jobject["payload"] = payload_object;
    QJsonDocument json_document(jobject);
    return json_document.toJson();
}

// This function will receive raw json message and two int pointer for returning detected
// status and type of the message.
// param json_message: QString raw received json message
// param status: integer pointer of status to returning the result
// param type: integer pointer of type to returning the result
// return: bool to indicate success or error of the parsing function
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

// This function will receive device name and create a protobuf configuration message for sending remote keys
// param device_name: QString name of the target device
// return: QByteArray of created protobuf message
QByteArray MessageHandler::ProtoBufConfigurationMessageCreator(const QString &device_name)
{
    std::vector<int> message_array = {1,0,0,21,0,0,0,1,0,0,0,1,32,3,0,0,0,0,0,0};
    QByteArray message;
    message_array.push_back(device_name.size());

    std::transform(device_name.begin(), device_name.end(), std::back_inserter(message_array),
                   [](QChar letter) -> int { return int(letter.toLatin1()); });

    std::transform(message_array.begin(), message_array.end(), std::back_inserter(message),
                   [](int item) -> char { return char(item); });

    return message;
}

// This function will receive key code, released flag and counter to create a protobuf key message
// param key_code: integer of key code
// param released: boolean of released flag
// param counter: integer of counter (continous message counter)
// return: QByteArray of created protobuf message
QByteArray MessageHandler::ProtoBufSendKeyMessageCreator(const int &key_code, const bool &released, const int &counter)
{
    std::vector<int> message_array = {1,2,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QByteArray message;
    message_array.push_back(key_code);
    // change counter value
    message_array[11] = counter;
    if (released) {
        // change press flag to release
        message_array[15] = 1;
    }

    std::transform(message_array.begin(), message_array.end(), std::back_inserter(message),
                   [](int item) -> char { return char(item);});
    return message;
}
