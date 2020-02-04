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
    y: 100
    visible: true

    property bool demo_run: true
    property int font_size: 30
    //property string font_name: "PingFang TC"
    //property string font_name: "Apple Color Emoji"
    //property string font_name: "Symbola"
    //property string font_name: "Bitstream Vera Sans"
    property string font_name: "Noto Emoji"
    //property string font_name: "DejaVu Sans"

    Timer {
        id: demo_timer
        interval: 750; running: demo_run; repeat: true
        onTriggered: {
            console.log('demo_timer onTriggered: ' + emoji.count);
            emoji.count += 1;
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        Column {
            padding: 12
            Row {
                padding: 20
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
                font.pointSize: font_size
                font.family: font_name
            }
            TextEdit {
                id: text_emoji
                color: "white"
                font.pointSize: font_size
                textFormat: TextEdit.RichText
                readOnly: true
                text: emoji.sequence
            }
        }

    }
}
