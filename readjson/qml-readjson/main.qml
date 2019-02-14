import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

ApplicationWindow
{
    width : 320; height: 240
    x: 800; y: 0
    title: "main window"
    id: root;
    visible: true
    color: 'steelblue'

    function updateDisplay(msg) {
        var s = msg["title"];
        if (s) {
            console.log("text: " + s);
            text_title.text = s;
        }
    }

    Connections {
        target: core
        onStateChanged: {
            console.log("onStateChanged...");
            updateDisplay(vm);
        }
    }

    Rectangle {
        id: button_area
        x: 0; y: 0
        anchors.fill: parent
        height: 40
        border.color: 'black'
        border.width: 1

        Button {
            id: start;
            text: "load and see";
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            onClicked: {
                console.log("button: load and see");
                core.test();
            }
        }

        Button {
            id: quit;
            text: "Quit";
            anchors.left: start.right
            anchors.leftMargin: 20;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            onClicked: {
                Qt.quit();
            }
        }

        Text {
            id: text_title
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: start.bottom
            anchors.topMargin: 20
            width: parent.width
            color: "#ababab"
            text: "default title"
            //font.family: fontRegular.name
            font.pixelSize: 40
            font.bold: true
            wrapMode: Text.NoWrap
            horizontalAlignment: Text.AlignHCenter
        }
    }

}
