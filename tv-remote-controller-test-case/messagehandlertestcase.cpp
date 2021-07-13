#include "messagehandlertestcase.h"

#include <QTest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "datamodel.h"
#include "messagehandler.h"

MessageHandlerTestCase::MessageHandlerTestCase()
{

}

void MessageHandlerTestCase::DialDeviceDescriptionParserTest()
{
    QUrl url("http://192.168.0.144:8008/apps/");
    QByteArray data("<?xml version=\"1.0\"?>\r\n<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\r\n  <specVersion>\r\n"
"    <major>1</major>\r\n    <minor>0</minor>\r\n  </specVersion>\r\n  <URLBase>http://192.168.0.144:8008</URLBase>\r\n"
"  <device>\r\n    <deviceType>urn:dial-multiscreen-org:device:dial:1</deviceType>\r\n    <friendlyName>Mi Box</friendlyName>\r\n"
"    <manufacturer>Xiaomi</manufacturer>\r\n    <modelName>MIBOX4</modelName>\r\n    <UDN>uuid:6184cf94-844c-9895-a7df-3dc0b3c19096</UDN>\r\n"
"    <iconList>\r\n      <icon>\r\n        <mimetype>image/png</mimetype>\r\n        <width>98</width>\r\n        <height>55</height>\r\n"
"        <depth>32</depth>\r\n        <url>/setup/icon.png</url>\r\n      </icon>\r\n    </iconList>\r\n    <serviceList>\r\n      <service>\r\n"
"        <serviceType>urn:dial-multiscreen-org:service:dial:1</serviceType>\r\n        <serviceId>urn:dial-multiscreen-org:serviceId:dial</serviceId>\r\n"
"        <controlURL>/ssdp/notfound</controlURL>\r\n        <eventSubURL>/ssdp/notfound</eventSubURL>\r\n        <SCPDURL>/ssdp/notfound</SCPDURL>\r\n"
"      </service>\r\n    </serviceList>\r\n  </device>\r\n</root>\r\n");
    DialDevice dial_device = MessageHandler::ParseDialDeviceDescription(url, data);
    QVERIFY(dial_device.friendly_name == "Mi Box");
    QVERIFY(dial_device.model_name == "MIBOX4");
    QVERIFY(dial_device.manufacturer_name == "Xiaomi");
    QVERIFY(dial_device.type == "urn:dial-multiscreen-org:device:dial:1");
    QVERIFY(dial_device.udn == "uuid:6184cf94-844c-9895-a7df-3dc0b3c19096");
    QVERIFY(dial_device.dial_rest_url == url);

}

void MessageHandlerTestCase::DialDeviceDescriptionParserTestInvalid()
{
    QUrl url{};
    QByteArray data{};
    DialDevice dial_device = MessageHandler::ParseDialDeviceDescription(url, data);
    QVERIFY(dial_device.friendly_name == "");
    QVERIFY(dial_device.model_name == "");
    QVERIFY(dial_device.manufacturer_name == "");
    QVERIFY(dial_device.type == "");
    QVERIFY(dial_device.udn == "");
    QVERIFY(dial_device.dial_rest_url == url);
}

void MessageHandlerTestCase::CreatePairingJsonMessageTest()
{
    QJsonDocument doc = QJsonDocument::fromJson(MessageHandler::CreatePairingRequestJsonMessage("test"));
    QJsonObject json_data = doc.object();
    QVERIFY(json_data["payload"].toObject()["client_name"].toString() == "test");
    QVERIFY(json_data["payload"].toObject()["service_name"].toString() == "androidtvremote");
    QVERIFY(json_data["status"].toInt() == 200);
    QVERIFY(json_data["type"].toInt() == 10);
    QVERIFY(json_data["protocol_version"].toInt() == 1);
}

void MessageHandlerTestCase::CreateOptionJsonMessageTest()
{
    QJsonDocument doc = QJsonDocument::fromJson(MessageHandler::CreateOptionJsonMessage());
    QJsonObject json_data = doc.object();
    QVERIFY(json_data["status"].toInt() == 200);
    QVERIFY(json_data["type"].toInt() == 20);
    QVERIFY(json_data["protocol_version"].toInt() == 1);
    QVERIFY(json_data["payload"].toObject()["preferred_role"].toInt() == 1);
    QVERIFY(json_data["payload"].toObject()["output_encodings"].toArray()[0].toObject()["symbol_length"] == 4);
    QVERIFY(json_data["payload"].toObject()["output_encodings"].toArray()[0].toObject()["type"] == 3);
    QVERIFY(json_data["payload"].toObject()["input_encodings"].toArray()[0].toObject()["symbol_length"] == 4);
    QVERIFY(json_data["payload"].toObject()["input_encodings"].toArray()[0].toObject()["type"] == 3);
}

void MessageHandlerTestCase::CreateConfigurationJsonMessageTest()
{
    QJsonDocument doc = QJsonDocument::fromJson(MessageHandler::CreateConfigurationJsonMessage());
    QJsonObject json_data = doc.object();
    QVERIFY(json_data["status"].toInt() == 200);
    QVERIFY(json_data["type"].toInt() == 30);
    QVERIFY(json_data["protocol_version"].toInt() == 1);
    QVERIFY(json_data["payload"].toObject()["client_role"].toInt() == 1);
    QVERIFY(json_data["payload"].toObject()["encoding"].toObject()["symbol_length"] == 4);
    QVERIFY(json_data["payload"].toObject()["encoding"].toObject()["type"] == 3);
}

void MessageHandlerTestCase::CreateSecretJsonMessageTest()
{
    QString secret_hash = "test";
    QJsonDocument doc = QJsonDocument::fromJson(MessageHandler::CreateSecretJsonMessage(secret_hash));
    QJsonObject json_data = doc.object();
    QVERIFY(json_data["status"].toInt() == 200);
    QVERIFY(json_data["type"].toInt() == 40);
    QVERIFY(json_data["protocol_version"].toInt() == 1);
    QVERIFY(json_data["payload"].toObject()["secret"].toString() == secret_hash);
    QJsonObject jobject, payload_object;
}

void MessageHandlerTestCase::JsonMessageParserTest()
{
    int type{}, status{};

    QJsonObject jobject, payload_object;
    payload_object["service_name"] = "androidtvremote";
    payload_object["client_name"] = "test";

    jobject["protocol_version"] = 1;
    jobject["type"] = 10;
    jobject["status"] = 200;
    jobject["payload"] = payload_object;
    QJsonDocument json_document(jobject);
    QVERIFY(MessageHandler::JsonMessageParser(json_document.toJson(), status, type));
    QVERIFY(type == 10);
    QVERIFY(status == 200);
}

void MessageHandlerTestCase::JsonMessageParserTestInvalid()
{
    int type{}, status{};
    QByteArray json_data = "{\"name\":1";
    QVERIFY(!MessageHandler::JsonMessageParser(json_data, status, type));
    QVERIFY(type == 0);
    QVERIFY(status == 0);
}

void MessageHandlerTestCase::ProtoBufConfigurationMessageCreatorTest()
{
    std::vector<int> arr = {1,0,0,21,0,0,0,1,0,0,0,1,32,3,0,0,0,0,0,0,4,116,101,115,116};
    QByteArray message;
    for (const auto& item: arr) {
        message.append(char(item));
    }
    QVERIFY(MessageHandler::ProtoBufConfigurationMessageCreator("test") == message);
}

void MessageHandlerTestCase::ProtoBufSendKeyMessageCreatorTest()
{
    std::vector<int> arr = {1,2,0,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24};
    QByteArray message;
    for (const auto& item: arr) {
        message.append(char(item));
    }
    QVERIFY(MessageHandler::ProtoBufSendKeyMessageCreator(24, false, 0) == message);
}

void MessageHandlerTestCase::ProtoBufSendKeyMessageCreatorTestRelease()
{
    std::vector<int> arr = {1,2,0,16,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,25};
    QByteArray message;
    for (const auto& item: arr) {
        message.append(char(item));
    }
    QVERIFY(MessageHandler::ProtoBufSendKeyMessageCreator(25, true, 1) == message);
}
