import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Demo: image - transform - rotation")
    x: 0; y: 0
    width: 400
    height: 400
    visible: true

    Timer {
        interval: 250; running: true; repeat: true
        onTriggered: {
            rr0.angle = ( rr0.angle + 15 ) % 360;
        }
    }
    Row {
        x: 60; y: 60;
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
        }
    }
}
