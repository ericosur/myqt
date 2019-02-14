import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

import "fsread.js" as FsRead

ApplicationWindow {
    width : 800; height: 600
    title: "main window"
    id: root;
    visible: true

    property var fn_num: 0;
    property var jsonobj;

    // test function
    function getjson() {
        var jsonstring = `
        {
            "msecsSinceEpoch": 1515046387408,
            "title": "逢いたくていま",
            "albumTitle": "逢いたくていま",
            "albumArtist": "MISIA",
            "position": 21000,
            "duration": 276000,
            "state" : "play",
            "image": "/home/rasmus/Pictures/data/box.png",
        }`;
        //return FsRead.getObjFromString( jsonstring );
        // read json file as a string, and parse it into js obj
    }

    function test() {

    }


    Connections {
        target: core
        /*
        onJsonstringChanged: {
            console.log("onJsonstringChanged: ");
            //console.log("jsonstring: " + core.jsonstring);
            //jsonobj = FsRead.getObjFromString(core.jsonstring);
            //console.log(jobj['image'])
            //update();
        }
        */
        onLhsChanged: {
            left_side.visible = true;
            right_side.visible = true;
        }
        onRhsChanged: {
            left_side.visible = true;
            right_side.visible = true;
        }
    }

    Rectangle {
        id: button_area
        x: 0; y: 0
        width: parent.width
        height: 40
        border.color: 'black'
        border.width: 1

        Button {
            id: start;
            text: "load and go";
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            onClicked: {
                console.log("button: load and go");
                test();
            }
        }

        Button {
            id: quit;
            text: "Quit";
            anchors.left: start.right
            anchors.leftMargin: 20;
            anchors.bottom: start.bottom;
            onClicked: {
                Qt.quit();
            }
        }
    }

    Rectangle {
        id: right_side
        width: 400
        anchors.top: button_area.bottom
        anchors.left: parent.left
        border.color: 'blue'
        border.width: 1
        Lhs {
            id: lhs_widget
        }
    }
    Rectangle {
        id: left_side
        width: 400
        anchors.top: button_area.bottom
        anchors.left: right_side.right
        Rhs {
            id: rhs_widget
        }

    }
}
