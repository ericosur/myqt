import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import "fact.js" as Fact

ApplicationWindow {
    id: root
    title: qsTr("Hello World")
    width: core.coreWidth
    height: core.coreHeight
    visible: true
    x: 50; y: 50

    property int header_height: 80
    property int footer_height: 100
    property int padding_height: 10
    property int img_height: 500
    property int img_width: 500

    Rectangle {
        id: blackbox
        anchors.fill: parent
        //color: "black"
        MouseArea {
            id: ma_blackbox
            anchors.fill: parent
        }
        Component.onCompleted: {
            color = Qt.binding(function() {
                return ma_blackbox.pressed ? "dimgrey" : "darkslategray";
            });
        }
    }

    Rectangle {
        id: bluebox
        x: 0; y: 0
        width: parent.width
        height: header_height - padding_height
        //border.width: 1
        //border.color: "steelblue"
        color: mousearea.pressed ? "slategrey" : "steelblue";

        MouseArea {
            id: mousearea
            anchors.fill: parent
            onClicked: {
                console.log("call Fact...");
                console.log(Fact.fact(5));
            }
        }
    }

    Flipable {
        id: flipable
        x: (parent.width - img_width) / 2
        y: (parent.height - img_height - footer_height) / 2 + bluebox.height + padding_height
        width: img_width
        height: img_height

        property bool flipped: false

        front: Image {
            source: "prev.jpg";
            anchors.centerIn: parent;
            width: parent.width; height: parent.height
        }
        back: Image {
            source: "next.jpg";
            anchors.centerIn: parent;
            width: parent.width; height: parent.height
        }
        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis.x: 0; axis.y: 1; axis.z: 0     // set axis.y to 1 to rotate around y-axis
            angle: 0    // the default angle
        }
        states: State {
            name: "back"
            PropertyChanges { target: rotation; angle: 180 }
            when: flipable.flipped
        }
        transitions: Transition {
            NumberAnimation { target: rotation; property: "angle"; duration: 2000 }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: flipable.flipped = !flipable.flipped
        }
    }
}
