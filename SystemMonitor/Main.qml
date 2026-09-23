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
    Text{
        text: "Процесор: " + monitor.processorName
        font.pixelSize: 16
        font.italic: true
        font.bold: true
        color: "white"
        anchors.left: parent.left
        anchors.leftMargin: 5
    }

    Rectangle{
        id: first_item
        width: main_rec.width-10
        height: parent.height/3.3
        anchors.top:parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 21
        color:"#737272"

        CircularGauge {
                id: first
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 12
                value: monitor.cpuUsage
                label: "CPU"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: second
                anchors.left: first.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 18
                value: monitor.usageRAM
                label: "RAM"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: third
                anchors.left: second.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 18
                value: monitor.usageMb
                maximumValue: monitor.totalMb
                unit: "/" + Math.round(monitor.totalMb)
                label: "RAM (Mb)"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: fourth
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                value: 0
                label: "CPU"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
    }
    Text{
        text: "Відеокарта: " + gpu.gpuName
        font.pixelSize: 16
        font.italic: true
        font.bold: true
        color: "white"
        anchors.top: first_item.bottom
        anchors.left: parent.left
        anchors.leftMargin: 5
    }
    Rectangle{
        id: second_item
        width: main_rec.width-10
        height: parent.height/3.3
        anchors.top:first_item.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 21
        color:"#737272"
        CircularGauge {
                id: first_2
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 12
                value: gpu.gpuUsagePer
                label: "GPU"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: second_2
                anchors.left: first_2.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 18
                value: gpu.gpuTem
                label: "GPU"
                width: 140
                height: 140
                progressColor: "#4CAF50"
                unit: "°C"

            }
        CircularGauge {
                id: third_2
                anchors.left: second_2.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 18
                value: gpu.usedMemoryMB
                 maximumValue: gpu.totalMemoryMB
                label: "VRAM (Mb)"
                unit: "/" + Math.round(gpu.totalMemoryMB)
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
        CircularGauge {
                id: fourth_2
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                value: 0
                label: "CPU"
                width: 140
                height: 140
                progressColor: "#4CAF50"

            }
    }
    Rectangle{
        id: third_item
        width: main_rec.width-10
        height: parent.height/3.3
        anchors.top:second_item.bottom
        anchors.bottom:parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.bottomMargin: 5
        color:"#737272"

    }
}
}
