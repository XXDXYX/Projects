import QtQuick
import QtQuick.Shapes

Item {
    id: root

    // --- Публичный API компонента ---
    property real value: 0
    property real maximumValue: 100
    property color trackColor: "#3A3A3A"
    property color progressColor: "#4CAF50"
    property string label: ""
    property int strokeWidth: 12

    implicitWidth: 160
    implicitHeight: 160

    // 1. Анимируем само входное значение, а не внутренности ShapePath!
    Behavior on value {
        NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
    }

    readonly property real ratio: maximumValue > 0
        ? Math.min(Math.max(value / maximumValue, 0), 1)
        : 0

    // Вспомогательные свойства для геометрии дуги (внутри Shape с margins)
    readonly property real arcCenterX: width / 2 - strokeWidth / 2
    readonly property real arcCenterY: height / 2 - strokeWidth / 2
    readonly property real arcRadius: (width - strokeWidth) / 2

    // --- Фоновая дуга (полный круг-трек) ---
    Shape {
        anchors.fill: parent
        anchors.margins: root.strokeWidth / 2
        antialiasing: true

        ShapePath {
            strokeWidth: root.strokeWidth
            strokeColor: root.trackColor
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            // 2. Указываем начальную точку пути.
            // Для -90 градусов X совпадает с центром, а Y поднят на радиус (равен 0)
            startX: root.arcCenterX
            startY: 0

            PathAngleArc {
                centerX: root.arcCenterX
                centerY: root.arcCenterY
                radiusX: root.arcRadius
                radiusY: root.arcRadius
                startAngle: -90
                sweepAngle: 359.9
            }
        }
    }

    // --- Активная дуга (показывает текущее значение) ---
    Shape {
        anchors.fill: parent
        anchors.margins: root.strokeWidth / 2
        antialiasing: true

        ShapePath {
            strokeWidth: root.strokeWidth
            // Бонус: скрываем "точку" (RoundCap), если прогресс равен 0
            strokeColor: root.ratio > 0 ? root.progressColor : "transparent"
            fillColor: "transparent"
            capStyle: ShapePath.RoundCap

            startX: root.arcCenterX
            startY: 0

            PathAngleArc {
                centerX: root.arcCenterX
                centerY: root.arcCenterY
                radiusX: root.arcRadius
                radiusY: root.arcRadius
                startAngle: -90
                sweepAngle: root.ratio * 359.9
            }
        }
    }

    // --- Текст в центре ---
    Column {
        anchors.centerIn: parent
        spacing: 2

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: Math.round(root.value) + "%"
            color: "white"
            font.pixelSize: 24
            font.bold: true
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.label
            color: "#AAAAAA"
            font.pixelSize: 12
            visible: root.label.length > 0
        }
    }
}