import QtQuick 2.0
import QtQuick.Layouts 1.15

ListView {
    id: devicesList
    property alias devicesListModel: devicesList.model
    anchors.fill: parent
    clip: true
    delegate: Item {
        id: itemDelegate
        width: devicesList.width
        height: 50
        Rectangle {
            id: frameRectangle
            border.width: 2
            border.color: "#747778"
            color: "transparent"
            anchors.fill: parent
            anchors.rightMargin: app.style.spacingSmall
            anchors.leftMargin: app.style.spacingSmall
        }
        RowLayout {
            id: listItemRow
            spacing: app.style.spacingSmall
            anchors{
                verticalCenter: parent.verticalCenter
                top: parent.top
                left: parent.left
                leftMargin: itemClickable.pressed ? 10 : 0
            }

            Text {
                id: indexText
                text: index + 1
                color: "#bfbfbf"
                Layout.leftMargin: app.style.spacingMedium

            }
            Text {
                id: deviceName
                text: name
                color: "#bfbfbf"
                Layout.leftMargin: app.style.spacingXLarge
            }
            Text {
                id: deviceIp
                text: ip
                color: "#bfbfbf"
                Layout.leftMargin: app.style.spacingXLarge
            }
        }
        MouseArea {
            id: itemClickable
            anchors.fill: parent
            onClicked: app.remoteController.pairDevice(name, ip)

        }
    }
}
