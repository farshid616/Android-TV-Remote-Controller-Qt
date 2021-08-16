#ifndef REMOTECONTROLCORE_H
#define REMOTECONTROLCORE_H

#include <QObject>
#include "messagehandler.h"
#include "upnpdiscovery.h"
#include "pairinghandler.h"
#include "keycommandsender.h"
#include "keycodesenum.h"
#include "devicemodel.h"

// This class handle the whole process from discovering to sending keys and is a bridge to QML pages
class RemoteControlCore : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlCore(QObject *parent = nullptr);
    Q_INVOKABLE void setPairingKey(const QString& pairing_code);
    Q_INVOKABLE void sendKey(const int& key);
    Q_INVOKABLE DeviceModel* getDeviceModel();
    Q_INVOKABLE void pairDevice(const QString& device_name, const QString& device_ip);
    static QString getDeviceName() ;

signals:
    void enterPairingCode();
    void deviceNameChanged(const QString& device_name);

private slots:
    void DialDeviceDetected(const QUrl& dial_rest_url, const QByteArray& device_description);
    void onPairingFinished();

private:
    Q_PROPERTY(QString deviceName READ getDeviceName CONSTANT NOTIFY deviceNameChanged)
    UpnpDiscovery upnp_discovery_;
    PairingHandler pairing_handler_;
    KeyCommandSender command_sender_;
    DialDevice device_;
    DeviceModel device_model_;

};

#endif // REMOTECONTROLCORE_H
