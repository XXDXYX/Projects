import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic


ApplicationWindow {
    id: window
    width: 640
    height: 480
    minimumWidth: 200
    minimumHeight: 250
    visible: true

    Rectangle{
    id: main_rec
    anchors.fill: parent
    color:"#595958"
    Rectangle{
        id: first_item
        width: main_rec.width-10
        height: parent.height/3.02
        anchors.top:parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        color:"#737272"

        CircularGauge {
                id: first
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 5
                value: monitor.cpuUsage
                label: "CPU"
                width: 150
                height: 150
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: second
                anchors.left: first.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 7
                value: monitor.usageRAM
                label: "RAM"
                width: 150
                height: 150
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: third
                anchors.left: second.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 7
                value: monitor.usageMb
                maximumValue: monitor.totalMb
                unit: "/" + Math.round(monitor.totalMb)
                label: "RAM (Mb)"
                width: 150
                height: 150
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: fourth
                anchors.left: third.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 7

                value: 0
                label: "CPU"
                width: 150
                height: 150
                progressColor: "#4CAF50"

            }
    }
}
}
