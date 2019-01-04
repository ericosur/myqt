/// Rhs.qml

import QtQuick 2.4
import QtQuick.Controls 1.3

import "fsread.js" as FsRead

Item {
    id: _rhs
    width: 400
    height: 560

    property var jsonobj;

    function update() {
        var foo;
        foo = jsonobj['image'];
        if (foo) {
            console.log("no foo?");
        } else {
            console.log("got foo?");
            if (foo === "") {
                console.log("foo is empty string");
            }
        }
        img0.source = 'file://' + jsonobj['image'];
        image.text = jsonobj['image'];
        album.text = jsonobj['albumTitle'];
        artist.text = jsonobj['albumArtist'];
        title.text = jsonobj['title'];
        var foo = jsonobj['nosuch'];
        console.log("foo: " + foo);
        if (foo) {
            console.log("foo undefined?");
        } else {
            console.log("foo is:" + foo);
        }
    }

    Connections {
        target: core
        onJsonstringChanged: {
            if (visible) {
                console.log("onRhsChanged");
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
        border.color: 'orange'
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
