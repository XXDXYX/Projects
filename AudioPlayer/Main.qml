import QtQuick
import QtQuick.Controls
import QtQuick.Effects


ApplicationWindow{
    visible: true
    width: 1000
    height: 650
    color: "gray"
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#EDEBE4" }
            GradientStop { position: 0.5; color: "#DFDCD2" }
            GradientStop { position: 1.0; color: "#CFCBBE" }
        }
    }
  Rectangle{
        id: container
        width: 450
        height: 480
        anchors.centerIn: parent
        color: "transparent"
        Rectangle{
        id: foto
        height: 280
        width: 280
        anchors.top: parent.top
        clip: true
        color: "#f0f0f0"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 12
        radius: 20
        Image{
            id: albumArt
            width: parent.width
            height: parent.height
            source: audEng.albumArtBase64
            layer.enabled: true
                layer.effect: MultiEffect {
                    maskEnabled: true
                    maskSource: ShaderEffectSource {
                        sourceItem: Rectangle {
                            width: albumArt.width
                            height: albumArt.height
                            radius: 20
                        }
                    }
                }
}
}
        Text{
            id: songName
            text: audEng.get_song
            font.pixelSize: 35
            font.weight: Font.DemiBold
            font.family: "Inter, -apple-system, Roboto, sans-serif"
            color: "gray"
            anchors.top: foto.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
        }
        Text{
            id: artisName
            text: audEng.get_artist
            font.pixelSize: 25
            color: "gray"
            anchors.top: songName.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5

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
                    color: "#c4c4c4"
                    Rectangle {
                        width: slider.visualPosition * parent.width
                        height: parent.height
                        color: "gray"
                        radius: 3
                    }
            }

            Text{
                id:songBegin
                property int minutes: (audEng.position/1000)/60
                property int seconds: (audEng.position/1000)%60
                text: minutes + ":" + seconds
                anchors.top:parent.bottom
                anchors.left: parent.left
                leftPadding: 10
            }

            Text{
                id: songDuration
                property int minutes: (audEng.duration/1000)/60
                property int seconds: (audEng.duration/1000)%60
                text: minutes + ":" + seconds
                anchors.top: parent.bottom
                anchors.right: parent.right
                rightPadding: 5
            }

            handle: Image{
                x: slider.leftPadding + slider.visualPosition * (slider.availableWidth - width)
                y: slider.topPadding + slider.availableHeight / 2 - height / 2
                width:16
                height: 16
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
        Rectangle {
            id: vol
            width: 22
            height: 0
            clip: true
            anchors.bottom: volumeButton.top
            color: "transparent"
            anchors.right: parent.right
            anchors.rightMargin: 25
            Behavior on height {
                    NumberAnimation { duration: 200 }
                }
            Slider {
                id: volumeSlider
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.bottomMargin: 5
                anchors.bottom: parent.bottom
                orientation: Qt.Vertical
                from: 0
                to: 10
                value: 5
                onValueChanged: audEng.set_volume(value / 10)

                background: Rectangle {
                    x: volumeSlider.leftPadding + volumeSlider.availableWidth / 2 - width / 2
                    y: volumeSlider.topPadding

                    width: 4
                    height: volumeSlider.availableHeight
                    radius: 2
                    color: "#c4c4c4"

                    Rectangle {
                        width: parent.width
                        height: (1 - volumeSlider.visualPosition) * parent.height
                        color: "gray"
                        anchors.bottom: parent.bottom
                        radius: 2
                    }
                }

                handle: Image {
                    x: volumeSlider.leftPadding + volumeSlider.availableWidth / 2 - width / 2
                    y: volumeSlider.topPadding + volumeSlider.visualPosition * volumeSlider.availableHeight - height / 2
                    source: "sliderHandle.png"
                    width: 8
                    height: 8
                }
            }
        }

    Rectangle{
        id: volumeButton
        color: "transparent"
        width: 45
        height: 45
        anchors.bottom: panel.top
        anchors.bottomMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 20
        Image{
            source: "volumeOn"
            anchors.fill: parent
            fillMode: Image.Stretch
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
            onClicked:
                vol.height = vol.height > 0 ? 0 : 60
        }
    }
    Rectangle{
        id: add_button
        width: 45
        height: 45
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


