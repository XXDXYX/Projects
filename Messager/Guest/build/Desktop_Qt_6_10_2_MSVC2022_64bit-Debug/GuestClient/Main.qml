import QtQuick
import QtQuick.Controls
import QtQuick.Window
Window {
    id: mainWindow
    width: 600
    height: 400
    visible: true


    flags: Qt.FramelessWindowHint | Qt.Window
    color: "transparent"
    Component.onCompleted: {
         Guest.connect_Guest()
    }



    Rectangle {
        id: mainRectangle
        anchors.fill: parent
        color: "#F6F2F2"
        radius: 20
        Connections{
            target: Guest
            function onNewMessageReceived(text) {
                    chatModel.append({ "author": "Друг", "content": text })
                    chatView.positionViewAtEnd()
                }
        }
        antialiasing: true
        Rectangle {
            id: inputWrapper
            height: 40
            color: "white"
            border.color: "#F79B9B"
            border.width: 2
            radius: 20


            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 15

            TextInput {
                id: messageInput
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                verticalAlignment: Text.AlignVCenter

                font.pixelSize: 16
                color: "black"
                focus: true

                Text {
                    text: "Введите сообщение..."
                    color: "#bdc3c7"
                    visible: !messageInput.text
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                }
                onAccepted: {
                    if (text !== "") {
                        chatModel.append({
                            "author": "Я",
                            "content": text
                        })
                        chatView.positionViewAtEnd()
                        Guest.sendMessage(text);
                        text = ""
                    }
                }
            }
        }
        ListModel {
            id: chatModel
        }
        ListView {
            id: chatView
            anchors.top: header.bottom
            anchors.bottom: inputWrapper.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            model: chatModel
            clip: true
            delegate: Rectangle {
                width: chatView.width
                height: messageText.height + 20
                color: "transparent"
               Text {
                    id: messageText
                    text: model.author + ": " + model.content
                    width: parent.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: 14
                    color: "black"
                }
            }
        }
            Rectangle{
                id: header
                width: parent.width
                height: 60
                radius: 20
                anchors.top: parent
                anchors.left: parent
                color: "#F26262"


            Rectangle{
                anchors.bottom: parent.bottom
                anchors.left: parent
                width:parent.width
                height:12
                color:parent.color

            }
        }
    }
    Rectangle{
        id: line
        anchors.bottom: parent.bottom
        anchors.margins: 65
        width: parent.width
        height: 2
        color: "gray"
    }
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.color: "gray"
        border.width: 1.5
        radius: 20
        z: 100
    }
    MouseArea {
            anchors.fill: parent
            property point lastMousePos: Qt.point(0, 0)
            onPressed: (mouse) => {
                lastMousePos = Qt.point(mouse.x, mouse.y)
            }
            onPositionChanged: (mouse) => {
                let dx = mouse.x - lastMousePos.x
                let dy = mouse.y - lastMousePos.y
                mainWindow.x += dx
                mainWindow.y += dy
            }
        }
    RoundButton{
        id:closeButton
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 10
        anchors.topMargin: 10
        width: 25
        height: 25
        text: "X"
        onClicked: close()
        background: Rectangle{
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: closeButton.hovered ? "#DE1616" : header.color
            radius: width/2
            Behavior on color {
                       ColorAnimation { duration: 150 }
                   }
        }
    }
}
