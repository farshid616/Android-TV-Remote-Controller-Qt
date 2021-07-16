import QtQuick 2.0
import QtQuick.Layouts 1.15
import KeyCodes 1.0

Item {
    id:root

    RowLayout {
        id: keysLayout
        spacing: app.style.spacingSmall

        ColumnLayout {
            id: firstColumn
            Layout.leftMargin: app.style.spacingLarge
            Button {
                id: powerButton
                buttonImage: "resources/Resources/Power.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_POWER)
            }
            Button {
                id: backButton
                buttonImage: "resources/Resources/back.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_BACK)
            }
        }
        ColumnLayout {
            id: secondColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: leftButton
                buttonImage: "resources/Resources/left.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_DPAD_LEFT)
            }
        }
        ColumnLayout {
            id: thirdColumn
            Button {
                id: upButton
                buttonImage: "resources/Resources/up.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_DPAD_UP)
            }
            Button {
                id: okButton
                buttonImage: "resources/Resources/ok.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_DPAD_CENTER)
            }
            Button {
                id: downButton
                buttonImage: "resources/Resources/down.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_DPAD_DOWN)
            }
        }
        ColumnLayout {
            id: fourthColumn
            Button {
                id: rightButton
                buttonImage: "resources/Resources/right.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_DPAD_RIGHT)
            }
        }
        ColumnLayout {
            id: fifthColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: menuButton
                buttonImage: "resources/Resources/menu.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_MENU)
            }
            Button {
                id: homeButton
                buttonImage: "resources/Resources/home.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_HOME)
            }
        }
        ColumnLayout {
            id: sixthColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: volumeUpButton
                buttonImage: "resources/Resources/plus.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_VOLUME_UP)
            }
            Button {
                id: volumeDownButton
                buttonImage: "resources/Resources/minus.png"
                mouseArea.onClicked: app.remoteController.sendKey(KeyCodes.KEYCODE_VOLUME_DOWN)
            }
            Button {
                id: keyboardButton
                buttonImage: "resources/Resources/keyboard.png"
                mouseArea.onClicked: textInput.activeFocus ? keyboardButton.forceActiveFocus() : textInput.forceActiveFocus()
            }
        }
    }
    TextInput {
        id: textInput
        visible: false
        readonly property bool empty: textInput.text === ""
        anchors.bottom: parent.bottom
        height: 50
        width: 100
        font.pixelSize: app.style.textSizeMedium
        renderType: Text.NativeRendering
        selectByMouse: true
        clip: !empty


        Text {
            id: placeholder

            width: parent.width
            elide: Text.ElideRight
            font.pixelSize: textInput.font.pixelSize
            renderType: textInput.renderType
            visible: opacity > 0
            text: qsTr("Insert your phrase to search")

            Behavior on opacity {
                NumberAnimation {
                    easing.type: Easing.OutExpo
                    duration: style.durationFast
                }
            }
        }
    }
}
