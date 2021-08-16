#include "devicemodel.h"

// This function receive a device id and find and return the index
// of that device in the devide list
// param id: QVariant of device id
// return: QVariant of corespond device index in the device list
QVariant DeviceModel::indexAt(QVariant id)
{
    for(auto i=0; i< device_items_.size(); i++)
    {
        if(device_items_[i].index == id)
            return i;
    }
    return -1;
}

// This is constructor of the class
DeviceModel::DeviceModel(QObject *parent) : QAbstractListModel(parent)
{

}

// This function will add the given device to the model
// param device_info: DeviceInfo of device to add to the model
void DeviceModel::addDevice(const DeviceInfo& device_info)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    device_items_.push_back(device_info);
    endInsertRows();
    layoutChanged();
}

// This function is override of abstract list model data function
// to provide requested data corespond to the given role
// param index: QModelIndex index of the model item
// param role: int of the role type
// return: QVariant of requested data by the role
QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    Roles roles = (Roles)role;
    if(row >= device_items_.size())
        return QVariant();

    switch (roles) {
    case NameRole:
        return device_items_[row].device_name;
    case IpRole:
        return device_items_[row].device_ip;
    case IndexRole:
        return device_items_[row].index;
    default:
        return device_items_[row].device_name;
    }
    return QVariant();
}

// This function will provide the current number of the models row
// param parent: QModelIndex (unused)
// return: int of current total rows in model
int DeviceModel::rowCount(const QModelIndex &parent) const
{
    return device_items_.size();
}

// This function generate a hash of roles enum to their names (aliases)
// return: QHash<int, QByteArray> of roles to aliases
QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(DeviceModel::NameRole, "name");
    roles.insert(DeviceModel::IpRole, "ip");
    roles.insert(DeviceModel::IndexRole, "index");
    return roles;
}

