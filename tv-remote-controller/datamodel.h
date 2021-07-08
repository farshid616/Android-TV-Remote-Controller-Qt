#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QUrl>
#include <QString>

struct DialDevice
{
    QUrl dial_rest_url{};
    QString friendly_name{};
    QString model_name{};
    QString manufacturer_name{};
    QString type{};
    QString udn{};
};
#endif // DATAMODEL_H
