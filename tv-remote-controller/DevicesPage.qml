import QtQuick 2.0

Item {
    id: root
    DevicesListView {
        id: devicesList
        devicesListModel: remoteController.getDeviceModel()
    }
}
