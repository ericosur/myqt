import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    readonly property string emoji_font: "Apple Color Emoji"
    readonly property int pixelSize: 60
    property string emoji_str1: "👨🏻‍🦰"
    property string emoji_str2: "\uD83D\uDE1C\uD83D\uDE17\uD83D\uDE0A\uD83D\uDE1C\uD83D\uDE1D\uD83D\uDE1D\uD83D\uDE09"

    Rectangle {
        anchors.fill: parent
        width: 360
        height: 360
        border.width: 2
        border.color: "pink"
        Text {
            id: bwEmoji
            font.family: emoji_font
            font.pixelSize: pixelSize
            text: emoji_str1
            renderType: Text.NativeRendering
            anchors.top: parent.top
            anchors.margins: 10
            anchors.horizontalCenter: parent.horizontalCenter
            onTextChanged: {
                console.log(text);
            }
        }
        Text {
            id: clrEmoji
            font.family: emoji_font
            font.pixelSize: pixelSize
            text: emoji_str2
            renderType: Text.NativeRendering
            anchors.top: bwEmoji.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onTextChanged: {
                console.log(text);
            }
        }
    }
}
