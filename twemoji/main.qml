import QtQuick 2.0
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

    Rectangle {
        anchors.fill: parent
        color: "black"
        TextEdit {
            color: "white"
            font.pointSize: 30
            textFormat: TextEdit.RichText
            readOnly: true
            text: emoji.sequence
        }
    }
}
