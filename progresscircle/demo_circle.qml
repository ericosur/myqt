import QtQuick 2.0
import QtQml 2.2

Item {
    width: 800
    height: 450
    property int circle_size: 200

    Rectangle {
        id: rect_bg
        anchors.fill: parent
        color: "black"

        Row {
            anchors.centerIn: parent
            spacing: 10

            ProgressCircle {
                size: circle_size
                colorCircle: "#0092CC"
                colorBackground: "#E6E6E6"
                arcBegin: 0
                arcEnd: 270
                lineWidth: 10
            }

            ProgressCircle {
                size: circle_size
                colorCircle: "#FF3333"
                colorBackground: "#E6E6E6"
                showBackground: true
                arcBegin: 0
                arcEnd: 210
            }

            ProgressCircle {
                size: circle_size
                colorCircle: "#779933"
                colorBackground: "#E6E6E6"
                showBackground: true
                isPie: true
                arcBegin: 90
                arcEnd: 200
            }
        }
    }
}
