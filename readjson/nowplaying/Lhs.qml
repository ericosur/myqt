/// Lhs.qml
import QtQuick 2.4
import QtQuick.Controls 1.3

import "fsread.js" as FsRead

Item {
    id: _lhs
    width: 400
    height: 560

    property var jsonobj;

    function update() {
        img0.source = 'file://' + jsonobj['image'];
        image.text = jsonobj['image'];
        album.text = jsonobj['albumTitle'];
        artist.text = jsonobj['albumArtist'];
        title.text = jsonobj['title'];

        //console.log(obj);
    }

    Connections {
        target: core
        onJsonstringChanged: {
            if (visible) {
                console.log("onLhsChanged");
                jsonobj = FsRead.getObjFromString(core.jsonstring);
                update();
            }
        }
    }

    Rectangle {
        id: text_area
        anchors.top: parent.top
        anchors.left: parent.left;
        width: parent.width; height: 100;
        border.color: 'yellow'
        border.width: 2

        Text {
            id: image
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            font.pixelSize: 16;
            text: "image"
        }
        Text {
            id: artist
            anchors.top: image.bottom
            anchors.topMargin: 4;
            anchors.left: parent.left
            anchors.leftMargin: 4;
            font.pixelSize: 16;
            text: "artist"
        }
        Text {
            id: album;
            anchors.top: artist.bottom;
            anchors.topMargin: 4;
            anchors.left: parent.left
            anchors.leftMargin: 4;
            font.pixelSize: 16;
            text: "album"
        }
        Text {
            id: title;
            anchors.top: album.bottom;
            anchors.topMargin: 4;
            anchors.left: parent.left
            anchors.leftMargin: 4;
            font.pixelSize: 16;
            text: "title"
        }
    }

    Rectangle {
        id: area1
        anchors.top: text_area.bottom
        width: parent.width; height: 460; //parent.height
        border.color: 'pink'
        border.width: 1

        Image{
            id: img0
            width: 400; height: 400;
        }
    }

}
