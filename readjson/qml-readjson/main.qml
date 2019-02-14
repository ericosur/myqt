import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

ApplicationWindow
{
    id: root;
    width : 400; height: 240
    x: 0; y: 0
    title: "readjson demo"
    visible: true
    color: 'steelblue'

    function updateDisplay(msg) {
        var s = msg["title"];
        if (s) {
            console.log("text: " + s);
            text_title.text = s;
        }
        s = msg["comment"];
        if (s) {
            console.log("comment: " + s);
            text_comment.text = s;
        }
        s = msg["extra"];
        if (s) {
            console.log("extra: " + s);
            text_extra.text = s;
        }
    }

    Connections {
        target: core
        onStateChanged: {
            console.log("onStateChanged...");
            updateDisplay(vm);
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Open..."
                shortcut: "Ctrl+O"
                onTriggered: core.test();
            }
            MenuItem {
                text: "Close"
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit();
            }
        }
    }


    Column {
        id: colu_area
        anchors.top: parent.top
        anchors.topMargin: 10
        // anchors.left: parent.left
        // anchors.leftMargin: 10
        spacing: 4
        Rectangle {
            color: "lightgrey"
            height: 40
            width: root.width
            Text {
                id: text_title
                anchors.fill: parent
                color: "#ababab"
                text: "default title"
                font.pixelSize: 36
                font.bold: true
                wrapMode: Text.NoWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            color: "lightgrey"
            height: 80
            width: root.width
            Text {
                id: text_comment
                anchors.fill: parent
                color: "darkgreen"
                text: "default comment"
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle {
            color: "lightgrey"
            height: 40
            width: root.width
            Text {
                id: text_extra
                anchors.fill: parent
                color: "indigo"
                text: "extra comment"
                font.pixelSize: 24
                font.bold: true
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

}
