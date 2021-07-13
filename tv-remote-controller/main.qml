import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Layouts 1.15

Window {
    id: app
    readonly property Style style: Style{}
    width: 800
    height: 600
    visible: true
    title: qsTr("Android TV Remote Control")

    Rectangle {
        id:input
        color: "#3e444a"
        anchors.centerIn: parent
        anchors.fill: parent

        RowLayout {
            id: header
            width: parent.width
            height: 40
            Text {
                id: deviceTest
                text: qsTr("No device found!")
                leftPadding: app.style.spacingLarge
                topPadding: app.style.spacingSmall
            }
            Rectangle {
                anchors.right: parent.right
                width: 60
                height: parent.height
                color: "transparent"
                anchors.rightMargin: app.style.spacingMedium
                Image {
                    id: headerButton
                    source: "file"
                }
            }
        }
//    InputPanel {
//        id: inputPanel
//        z: 99
//        x: 0
//        y: window.height
//        width: window.width


//        states: State {
//            name: "visible"
//            when: inputPanel.active
//            PropertyChanges {
//                target: inputPanel
//                y: window.height - inputPanel.height
//            }
//        }
//        transitions: Transition {
//            from: ""
//            to: "visible"
//            reversible: true
//            ParallelAnimation {
//                NumberAnimation {
//                    properties: "y"
//                    duration: 250
//                    easing.type: Easing.InOutQuad
//                }
//            }
//        }
//    }
    }
}
