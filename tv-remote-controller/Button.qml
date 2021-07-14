import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    property alias buttonText: buttonText
    property alias buttonImage: buttonImage.source
    property alias mouseArea: mouseArea
    property bool selection: false

    Layout.minimumWidth: 40
    Layout.minimumHeight: 40
    color: "transparent"

    Text{
        id:buttonText
        font.italic: true
        font.pixelSize: app.style.textSizeSmall
        color: "white"
        anchors.centerIn: root
    }
    Image {
        id: buttonImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }
    MouseArea {
        id:mouseArea
        anchors.fill: root
    }
    Glow {
        id: repeatGlow
        anchors.fill: buttonImage
        radius: 20
        samples: 20
        color: app.style.colorGlow
        source: buttonImage
        visible: mouseArea.pressed
    }

}
