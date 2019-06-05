import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    id: mainwindow
    title: "Hell World"
    width: 640
    height: 480
    x: 100
    y: 0
    visible: true


    Text {
        text: emoji.sequence
    }
}
