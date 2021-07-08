#include "messagehandlertestcase.h"

#include <QTest>
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
