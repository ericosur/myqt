import QtQuick 2.6
import QtQml 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    id: mainwindow
    title: "Hell World"
    width: 800
    height: 240
    x: 100
    y: 0
    visible: true

    property bool demo_run: true

    Timer {
        id: demo_timer
        interval: 1500; running: demo_run; repeat: true
        onTriggered: {
            console.log('demo_timer onTriggered');
            emoji.count += 1;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        Column {
            padding: 12
            Row {
                padding:10
                Button {
                    text: "Pause"
                    onClicked: {
                        console.log("paused!");
                        demo_run = !demo_run;
                    }
                }
                Button {
                    text: "Quit"
                    onClicked: {
                        console.log("quit!");
                        mainwindow.close();
                    }
                }
            }
            Text {
                color: "steelblue"
                text: emoji.instr
                font.pointSize: 24
                font.family: "Bitstream Vera Sans"
            }
            TextEdit {
                id: text_emoji
                color: "white"
                font.pointSize: 30
                textFormat: TextEdit.RichText
                readOnly: true
                text: emoji.sequence
            }
        }

    }
}
