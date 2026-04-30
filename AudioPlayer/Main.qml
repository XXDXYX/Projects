
import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow{
    visible: true
    width: 1000
    height: 650

     Component.onCompleted: {
         audEng.play();
     }
    Rectangle{
        color: "white";
        anchors.fill: parent
        Image {
            id: photo
            source: "photo.png"
            width: 320
            height: 408
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.topMargin: 0
            y: 0
         }
    }
    Rectangle{
        id: panel
        color: "transparent"
        width: 950
        height: 80


        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 8
        Rectangle{
        id: start_bottom
        width:45
         height: 45
         color: "transparent"
         anchors.bottom: parent.bottom
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.bottomMargin: 2
         radius: width * 0.5
         Image{
            source: "play.png"
            anchors.fill: parent
            fillMode: Image.Stretch
         }

        }
    }
}
