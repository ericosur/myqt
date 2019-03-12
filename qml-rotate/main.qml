import QtQuick 2.6
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Demo: image - transform - rotation")
    x: 0; y: 0
    width: 640
    height: 480
    visible: true

    Timer {
        interval: 250; running: true; repeat: true
        onTriggered: {
            rr0.angle = ( rr0.angle + 15 ) % 360;
        }
    }

    Rectangle {
        id: rec0
        x: 0; y: 0
        width: parent.width
        height: 200
        border.width: 2
        border.color: "pink"
        color: "black"
        Text {
            id: text_test
            anchors.fill: parent
            //font.family: "DejaVu Sans"
            font.family: "VC1"
            font.pointSize: 36
            color: "white"
            wrapMode: Text.WordWrap
            topPadding: 10
            leftPadding: 10
            text: " WMVYA QUICK FOX JUMPS OVER THE LAZY DOG "
        }
    }

    Row {
        x: 60;
        anchors.top: rec0.bottom
        spacing: 80;
        Image {
            id: img
            width: 200
            height: 200
            source: "circle.png"
            transform: [
                Rotation {
                    id: rr0;    angle: 0
                    origin.x: img.width/2; origin.y: img.height/2;
                    axis { x: 0; y: 0; z: 1 }
                }
                ,Rotation {
                    id: rr1;    angle: 60
                    origin.x: img.width/2; origin.y: img.height/2;
                    axis { x: 1; y: 0; z: 0}
                }
            ]
        }
        Text {
            id: text_angle
            text: rr0.angle
            font.pointSize: 40
        }
    }
}
