import QtQuick 2.0
import QtQuick.Layouts 1.15

Item {
    id:root
//    Rectangle {
//        anchors.fill: parent
//        color: "purple"
//    }

    RowLayout {
        id: keysLayout
        spacing: app.style.spacingSmall

        ColumnLayout {
            id: firstColumn
            Layout.leftMargin: app.style.spacingLarge
            Button {
                id: powerButton
                buttonImage: "resources/Resources/Power.png"
            }
            Button {
                id: backButton
                buttonImage: "resources/Resources/back.png"
            }
        }
        ColumnLayout {
            id: secondColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: leftButton
                buttonImage: "resources/Resources/left.png"
            }
        }
        ColumnLayout {
            id: thirdColumn
            Button {
                id: upButton
                buttonImage: "resources/Resources/up.png"
            }
            Button {
                id: okButton
                buttonImage: "resources/Resources/ok.png"
            }
            Button {
                id: downButton
                buttonImage: "resources/Resources/down.png"
            }
        }
        ColumnLayout {
            id: fourthColumn
            Button {
                id: rightButton
                buttonImage: "resources/Resources/right.png"
            }
        }
        ColumnLayout {
            id: fifthColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: menuButton
                buttonImage: "resources/Resources/menu.png"
            }
            Button {
                id: homeButton
                buttonImage: "resources/Resources/home.png"
            }
        }
        ColumnLayout {
            id: sixthColumn
            Layout.leftMargin: app.style.spacingXXLarge
            Button {
                id: volumeUpButton
                buttonImage: "resources/Resources/plus.png"
            }
            Button {
                id: volumeDownButton
                buttonImage: "resources/Resources/minus.png"
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
//        anchors.right: parent.right
//        anchors.leftMargin: app.style.spacingSmall
        height: 50
        width: 100
//        verticalAlignment: TextInput.AlignVCenter
        font.pixelSize: app.style.textSizeMedium
        renderType: Text.NativeRendering
        selectByMouse: true
//        color: style.colorTextPrimary
//        selectionColor: style.colorTextSelection
        clip: !empty


        Text {
            id: placeholder

//            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            elide: Text.ElideRight
//            color: style.colorTextHint
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
