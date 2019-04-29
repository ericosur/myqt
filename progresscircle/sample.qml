import QtQuick 2.0
import QtQml 2.2

Item {
    width: 800
    height: 450

    Rectangle {
        id: rect_bg
        anchors.fill: parent
        color: "black"
        Row {
            anchors.centerIn: parent
            spacing: 10
            Image {
                id: img0
                width: 400
                height: 400
                source: "./svg/roundabout_base.svg"
            }

            Image {
                height: img0.height
                width: img0.width
                //opacity: 0.8
                source: "./svg/roundabout_right.svg"
            }
        }
    }
}
