#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QUrl>
#include <QString>

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
#endif // DATAMODEL_H
