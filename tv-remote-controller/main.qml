import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Layouts 1.15
import RemoteController 1.0

Window {
    id: app
    readonly property Style style: Style{}
    property alias remoteController: remoteController
    property bool settingsActivated: false
    width: 720
    height: 500
    visible: true
    title: qsTr("Android TV Remote Control")

    RemoteController {
        id:remoteController
        onEnterPairingCode: codeInput.visible = true
    }

    Rectangle {
        id:input
        color: "#3e444a"
        anchors.centerIn: parent
        anchors.fill: parent


        RowLayout {
            id: header
            width: app.width
            height: app.height / 12
            Text {
                id: deviceTest
                text: remoteController.deviceName === "" ? qsTr("No device found!") : remoteController.deviceName
                leftPadding: app.style.spacingLarge
                topPadding: app.style.spacingSmall
                color: "#919191"
            }

            Button {
                id: settingsButton
                width: app.height / 10
                height: parent.height
                Layout.alignment: Qt.AlignRight
                Layout.rightMargin: app.style.spacingMedium
                Layout.topMargin: app.style.spacingSmall
                buttonImage: "/resources/Resources/setting.png"
                mouseArea.onClicked: {

                    animation.running = true
                    settingsActivated = !settingsActivated
                    loaderAnimation.running = true
                    settingsButton.buttonImage = settingsActivated ? "/resources/Resources/home.png" :
                                                                     "/resources/Resources/setting.png"
                    loader.source = !settingsActivated? "KeysPage.qml" : "DevicesPage.qml"
                }

                NumberAnimation {
                    id: animation
                    target: settingsButton
                    property: "rotation"
                    from: 0
                    to: 360
                    duration: 800
                    easing.type: Easing.InExpo
                }
            }
        }
        Loader {
            id: loader
            anchors.top: header.bottom
            anchors.topMargin: app.style.spacingMedium
            width: app.width
            height: app.height / 1.1
            source: "KeysPage.qml"
            NumberAnimation {
                id: loaderAnimation
                target: loader
                property: "opacity"
                from: 0
                to: 1
                duration: 800
                easing.type: Easing.InExpo
            }
        }


    }
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: app.height
        width: app.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: app.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
    CodeInput {
        id: codeInput
        anchors.fill: parent
        visible: false
        onAccepted: remoteController.setPairingKey(codeText.text)
    }
}
