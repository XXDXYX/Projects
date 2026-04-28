
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
}
