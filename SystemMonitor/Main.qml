import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

ApplicationWindow {
    id: window


    width: 610
    height: 520

    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height

    visible: true
    title: "appSystemMonitor"

    Rectangle {
        id: main_rec
        anchors.fill: parent
        color: "#595958"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 8
            spacing: 4


            Text {
                text: "Процесор: " + monitor.processorName
                font.pixelSize: 16
                font.italic: true
                font.bold: true
                color: "white"
                Layout.leftMargin: 6
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 148
                color: "#737272"

                Row {
                    anchors.centerIn: parent
                    spacing: 10

                    CircularGauge {
                        value: monitor.cpuUsage
                        label: "CPU"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: monitor.usageRAM
                        label: "RAM"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: monitor.usageMb
                        maximumValue: monitor.totalMb
                        unit: "/" + Math.round(monitor.totalMb)
                        label: "RAM (Mb)"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: monitor.procClock
                        label: "CPU Clock (мГц)"
                        unit: "MHz"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                }
            }


            Text {
                text: "Відеокарта: " + gpu.gpuName
                font.pixelSize: 16
                font.italic: true
                font.bold: true
                color: "white"
                Layout.leftMargin: 6
                Layout.topMargin: 2
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 148
                color: "#737272"

                Row {
                    anchors.centerIn: parent
                    spacing: 10

                    CircularGauge {
                        value: gpu.gpuUsagePer
                        label: "GPU"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: gpu.gpuTem
                        label: "GPU"
                        unit: "°C"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: gpu.usedMemoryMB
                        maximumValue: gpu.totalMemoryMB
                        label: "VRAM (Mb)"
                        unit: "/" + Math.round(gpu.totalMemoryMB)
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: gpu.gpuClock/1000
                        maximumValue: gpu.gpuTotalClock/1000
                        label: "GPU Clock (мГц)"
                        unit: "MHz"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                }
            }


            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 148
                Layout.topMargin: 2
                color: "#737272"

                Row {
                    anchors.centerIn: parent
                    spacing: 25

                    CircularGauge {
                        value: network.download
                        label: "Download speed"
                        unit: " Mb"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: network.upload
                        label: "Upload speed"
                        unit: " Mb"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }
                    CircularGauge {
                        value: monitor.battery
                        label: "Battery"
                        width: 140
                        height: 140
                        progressColor: "#4CAF50"
                    }

                }
            }
        }
    }
}