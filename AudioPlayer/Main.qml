
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
        id: start_and_stop_bottom
        width:45
         height: 45

         anchors.bottom: parent.bottom
         anchors.horizontalCenter: parent.horizontalCenter
         anchors.bottomMargin: 2
         color:  "transparent"
         radius: width * 0.5

         Image{
            id: start_stop_ico
            source: "play.png"
            anchors.fill: parent
            fillMode: Image.Stretch
         }
         MouseArea {

                 anchors.fill: parent
                 hoverEnabled: true
                 cursorShape: Qt.PointingHandCursor
                 onClicked:
                    if(start_stop_ico.source.toString().includes("play.png")){
                    start_stop_ico.source = "stop.png";

                        audEng.pause();
                    }else{
                      start_stop_ico.source = "play.png";

                        audEng.play();
                    }
                }
        }
        Rectangle{
            width: 45
            height: 45
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.left: start_and_stop_bottom.right
            anchors.leftMargin: 2
            color:  "transparent"
            radius: width * 0.5
            Image{
               id: right_button_ico
               source: "right.png"
               anchors.fill: parent
                fillMode: Image.Stretch
            }
            MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: audEng.track_forward();
            }
        }
        Rectangle{
            width: 45
            height: 45
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.right: start_and_stop_bottom.left
            anchors.leftMargin: 2
            color:  "transparent"
            radius: width * 0.5
            Image{
               id: left_button_ico
               source: "left.png"
               anchors.fill: parent
                fillMode: Image.Stretch
            }
            MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: audEng.track_back();
            }

        }
    }
    Rectangle{
        id: add_button
        width: 60
        height: 60
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 3
        anchors.rightMargin: 3
        color:"transparent"
        Image{
           source: "add_track.png"
           anchors.fill: parent
            fillMode: Image.Stretch
        }
        MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked:
                    audEng.load_track();
        }

    }


}


