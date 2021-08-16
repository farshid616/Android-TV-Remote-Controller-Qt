#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "datamodel.h"

// This class is a list model to provide a model for devices
class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_INVOKABLE QVariant nameAt(int index) { return device_items_[index].device_name; }
    Q_INVOKABLE QVariant ipAt(int index) { return device_items_[index].device_ip; }
    Q_INVOKABLE QVariant indexAt(QVariant id);
public:
    DeviceModel(QObject *parent = nullptr);
    enum Roles {
        DeviceRole = Qt::UserRole,
        NameRole,
        IpRole,
        IndexRole
    };Q_ENUM(Roles)
    void addDevice(const DeviceInfo& device_info);
    QVariant data(const QModelIndex& index, int role) const override;
    int rowCount(const QModelIndex& parent = {}) const override;

signals:

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    //List of the devices
    QVector<DeviceInfo> device_items_;
    //Pair of the rules and their names
    const QHash<int, QByteArray> role_names_ = roleNames();

};

#endif // DEVICEMODEL_H
