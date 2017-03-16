import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    x: 0 ; y: 0
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "darkgrey"

    ImageViewer {
        anchors.fill: parent
    }
}
