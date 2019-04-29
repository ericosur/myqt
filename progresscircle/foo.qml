import QtQuick 2.0
import QtQml 2.2

Item {
    width: 400
    height: 400

    Rectangle {
        anchors.fill: parent
        color: "black"
        Image {
            anchors.centerIn: parent
            source: "./svg/roundabout_base.svg"
        }

        Image {
            anchors.centerIn: parent
            opacity: 0.8
            source: "./svg/roundabout_left.svg"
        }
    }
}
