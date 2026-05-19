import QtQuick
import QtQuick.Controls

ApplicationWindow{
    visible: true
    width: 1000
    height: 650


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
            anchors.fill: parent
            fillMode: Image.Stretch
            source: audEng.isPlaying ? "play.png" : "stop.png"
         }
         MouseArea {
                 anchors.fill: parent
                 hoverEnabled: true
                 cursorShape: Qt.PointingHandCursor
                 onClicked:
                    if(audEng.isPlaying){
                        audEng.pause();
                    }else{
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
        Slider{
            id:slider
            anchors.top:parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            leftPadding: 8
            rightPadding: 8
            from:0
            to: audEng.duration;

            value:audEng.position;
            background: Rectangle {
                x: slider.leftPadding
                y: slider.topPadding + slider.availableHeight / 2 - height / 2
                implicitWidth: 200
                implicitHeight: 6
                width: slider.availableWidth
                    height: implicitHeight
                    radius: 3
                    color: "#E0E0E0"
                    Rectangle {
                        width: slider.visualPosition * parent.width
                        height: parent.height
                        color: "#000000"
                        radius: 3
                    }
            }

            handle: Image{
                x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
                y: slider.topPadding + slider.availableHeight / 2 - height / 2
                width:16
                height: 32
                source: "sliderHandle.png"
                HoverHandler {
                            cursorShape: Qt.PointingHandCursor
                        }
            }


            onValueChanged:
                if (slider.pressed) {
                    audEng.seek(value);
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


