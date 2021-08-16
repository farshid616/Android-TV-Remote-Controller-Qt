#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QUrl>
#include <QString>
#include <QVariant>

// Dial Device data type to soring dial device information
struct DialDevice
{
    QUrl dial_rest_url{};
    QString friendly_name{};
    QString model_name{};
    QString manufacturer_name{};
    QString type{};
    QString udn{};
};

// Enumeration for discovery state
enum DiscoveryState {
    StateIdle,
    StateSearching,
    StateError
};

// Device info type for uning in device model
struct DeviceInfo {
    int index{};
    QVariant device_name{};
    QVariant device_ip{};
    DeviceInfo(){};
    DeviceInfo(int index, QVariant name, QVariant ip) {
        this->index = index;
        this->device_name = name;
        this->device_ip = ip;
    }
};
#endif // DATAMODEL_H
