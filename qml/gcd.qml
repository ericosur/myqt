import QtQuick 2.9
import QtQuick.Window 2.2
import "gcd.js" as Gcd

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        text: Gcd.gcd(1200, 1080)

    }
}
