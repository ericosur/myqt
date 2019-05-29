import QtQuick 2.12

Item {
    id: _root

    // Noto Sans CJK TC
    // DejaVu Sans
    // DejaVu Serif
    // VC1
    property string fontName: "DejaVu Sans"
    property int fontSize: 24
    property string testString: "The quick brown fox jumps over the lazy dog"
    property int maxWidth: textMetrics.advanceWidth

    width: maxWidth + 20
    height: 240

    TextMetrics {
        id: textMetrics
        font.family: _root.fontName
        font.pixelSize: _root.fontSize
        elide: Text.ElideMiddle
        elideWidth: 200
        text: testString
    }

    Column {
        Text {
            id: _title
            text: 'Demo for qml TextMetrics'
            font.family: _root.fontName
            font.pixelSize: _root.fontSize
        }
        Text {
            text: 'font: ' + fontName
            font.family: _root.fontName
            font.pixelSize: _root.fontSize
        }
        Text {
            text: 'width: ' + textMetrics.advanceWidth
            font.family: _root.fontName
            font.pixelSize: _root.fontSize
        }
        Text {
            text: textMetrics.elidedText
            font.family: _root.fontName
            font.pixelSize: _root.fontSize
        }

        Text {
            text: textMetrics.text
            font.family: _root.fontName
            font.pixelSize: _root.fontSize
        }
    }
}
