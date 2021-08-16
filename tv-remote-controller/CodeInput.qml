import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id:root
    signal accepted
    property alias codeText: textInput
    Layout.minimumWidth: 640
    Layout.minimumHeight: 480
    visible: false

    Rectangle{
        id:bglayer
        anchors.fill: parent
        color:Qt.rgba(0,0,0,0.8)
        z:10

    }
    Rectangle {
        id: promptRectangle
        border.width: 1
        border.color: "grey"
        color: "#444347"
        width: 280
        height: 190
        anchors.top: parent.top
        anchors.horizontalCenter: bglayer.horizontalCenter
        anchors.topMargin: app.style.spacingXLarge
        z: 11

        ColumnLayout {
            id: column
            anchors.fill: parent

            Text {
                id: informationText
                text: qsTr("Please Enter the Pairing code:")
                color: "white"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: app.style.spacingLarge
                Layout.fillHeight: true
                Layout.minimumHeight: 40
                Layout.minimumWidth: 100
            }
            Rectangle {
                id: textInputRectangle
                Layout.alignment: Qt.AlignHCenter
                color: "#d5d4d6"
                border.color: "grey"
                border.width: 2
                Layout.minimumHeight: 30
                Layout.minimumWidth: 80

                TextInput {
                    id: textInput
                    anchors.fill: textInputRectangle
                    anchors.centerIn: textInputRectangle
                    anchors.topMargin: 8
                    anchors.leftMargin: 20
                    maximumLength: 4
                    color: "black"
                }
            }
            RowLayout {
                id: buttonsLayout
                Layout.alignment: Qt.AlignHCenter
                Layout.fillHeight: true
                Layout.minimumHeight: 60
                Layout.minimumWidth: 250
                Layout.topMargin: app.style.spacingMedium
                spacing: app.style.spacingLarge


                Button {
                    id: cancelButton
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.minimumHeight: 30
                    Layout.leftMargin: app.style.spacingLarge
                    color: "#d5d4d6"
                    border.color: "white"
                    border.width: 2
                    buttonText.text: "cancel"
                    buttonText.color: "black"
                    mouseArea.onPressed: color = "red"
                    mouseArea.onReleased: color = "#d5d4d6"
                    mouseArea.onClicked: root.visible = false
                }
                Button {
                    id: enterButton
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.minimumHeight: 30
                    Layout.rightMargin: app.style.spacingLarge
                    color: "#d5d4d6"
                    border.color: "white"
                    border.width: 2
                    buttonText.text: "enter"
                    buttonText.color: "black"
                    mouseArea.onPressed: color = "green"
                    mouseArea.onReleased: color = "#d5d4d6"
                    mouseArea.onClicked: {
                        root.visible = false
                        root.accepted()
                    }
                }
            }
        }
    }

}
