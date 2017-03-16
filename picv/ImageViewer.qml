import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {

    Image {
        id: picture_holder
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent
        source: imagectrl.imageUrl
    }

    Text {
        id: pic_name
        visible: true
        color: "black"
        text: imagectrl.imageUrl
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("clicked");
            //pic_name.text =
        }
    }


    TabBar {
        id: tabBar
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        currentIndex: 1
        TabButton {
            text: qsTr("Prev")
            onClicked: {
                imagectrl.goPrev();
            }
        }
        TabButton {
            text: qsTr("Auto")
            onClicked: {
                imagectrl.togglePlay();
            }
        }
        TabButton {
            text: qsTr("Next")
            onClicked: {
                imagectrl.goNext();
            }
        }
    }

    PageIndicator {
        id: indicator
        //count: imagectrl.showCount
        count: 10
        currentIndex: imagectrl.currentIndex
        anchors.bottom: tabBar.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

}
