import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 800
    height: 640
    visible: true

    Timer {
        interval: 250; running: true; repeat: true
        onTriggered: {
            //time.text = Date().toString();
            rr1.angle = ( rr1.angle + 15 ) % 360;
            rr2.angle = ( rr2.angle + 15 ) % 360;
            rr3.angle = ( rr3.angle + 15 ) % 360;
        }
    }
    //Text { id: time }
    Row {
        x: 10; y: 40
        spacing: 20
        Image { source: "hh.png" }
    }
    Row {
        x: 120; y: 260;
        spacing: 80;
        Image {
            source: "hh.png"
            transform: Rotation { id: rr1; origin.x: 30; origin.y: 30; axis { x: 1; y: 0; z: 0 } angle: 0 }
        }
        Image {
            source: "hh.png"
            transform: Rotation { id: rr2; origin.x: 30; origin.y: 30; axis { x: 0; y: 1; z: 0 } angle: 0 }
        }
        Image {
            source: "hh.png"
            transform: Rotation { id: rr3; origin.x: 30; origin.y: 30; axis { x: 0; y: 0; z: 1 } angle: 0 }
        }
    }
}
