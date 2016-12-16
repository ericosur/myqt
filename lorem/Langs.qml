import QtQuick 2.5
//import QtQuick.Window 2.2

Item {
    //visible: true
    width: 800
    height: 600

    property int box_width: 120
    property int box_height: 60
    property int box_gap: 12
    property int box_fontsize: 20
    //property var text_area_text: mytext.message

    Rectangle {
        id: rect1
        width: box_width; height: box_height
        x: 10; y: 10
        color: "transparent"
        border.color: "blue"; border.width: 2
        Text {
            anchors.fill: parent
            text: "English"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect1");
                mytext.getTextWithId(1);
            }
        }
    }
    Rectangle {
        id: rect2
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect1.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "العربية"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect2");
                mytext.getTextWithId(2);
            }
        }
    }
    Rectangle {
        id: rect3
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect2.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "português"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect3");
                mytext.getTextWithId(3);
            }
        }
    }
    Rectangle {
        id: rect4
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect3.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "français"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect4");
                mytext.getTextWithId(4);
            }
        }
    }
    Rectangle {
        id: rect5
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect4.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "español"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect5");
                mytext.getTextWithId(5);
            }
        }
    }
    Rectangle {
        id: rect6
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect5.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "русский"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect6");
                mytext.getTextWithId(6);
            }
        }
    }
    Rectangle {
        id: rect7
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect6.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "український"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect7");
                mytext.getTextWithId(7);
            }
        }
    }
    Rectangle {
        id: rect8
        width: box_width; height: box_height
        anchors.top: rect1.top
        anchors.left: rect7.right
        anchors.leftMargin: box_gap
        color: "transparent"
        border.color: "black"; border.width: 2
        Text {
            anchors.fill: parent
            text: "Japanese"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("rect8");
                mytext.getTextWithId(8);
            }
        }
    }

    Rectangle {
        id: text_area
        anchors.top: rect1.bottom
        anchors.topMargin: 50
        anchors.left: rect1.right
        anchors.leftMargin: 50
        width: 500; height: 500
        color: "transparent"
        border.color: "hotpink"; border.width: 2
        Text {
            id: text_area_text
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: box_fontsize + 4
            //text: mytext.getText()
        }
    }

}
