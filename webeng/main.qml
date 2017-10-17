import QtQuick 2.2
import QtQuick.Window 2.1
import QtWebEngine 1.2

import "fs-read.js" as FsRead

Window {
    x: 10; y: 10
    width: 1280
    height: 800
    visible: true
    id: main_window

    property var one_half: 0.5
    property var siriwave_page: core.local_left_url
    property var dnamusic_page: core.local_right_url
    property var googlemap_page: "https://www.google.com/maps"
    property var yweather_page: "https://tw.news.yahoo.com/weather"
    property var header_line: 10
    property var default_margin: 10
    property var deault_rect_height: 40
    property var deault_rect_width: 85
    property var rect0_height: 80

    property var config_left_url: core.default_left_url
    property var config_left_name: core.default_left_name
    property var config_right_url: core.default_right_url
    property var config_right_name: core.default_right_name

    function getRandomUrl() {
        if (true) {
            // using c++ json functions
            return core.getRandomUrl();
        }
        // read json file as a string, and parse it into js obj
        return FsRead.getUrlFromJsonString( core.jsonstring );
    }


    Rectangle {
        id: rect0
        width: parent.width
        height: rect0_height
        color: "steelblue"

        Rectangle {
            id: rect_seperate1
            anchors.top: parent.top
            x: parent.width / 6
            width: 2
            height: parent.height
            color: "pink"
        }
        Rectangle {
            id: rect_seperate2
            anchors.top: parent.top
            x: parent.width * one_half
            width: 2
            height: parent.height
            color: "pink"
        }

        Rectangle {
            id: rect_restore
            anchors.top: parent.top
            anchors.topMargin: header_line
            anchors.left: parent.left
            anchors.leftMargin: default_margin
            width: parent.width / 10
            height: parent.height / 4
            Text {
                text: "restore"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_restore
                anchors.fill: parent
                onClicked: {
                    console.log("restore!");
                    we1.url = siriwave_page;
                    we2.url = dnamusic_page;
                    right_pane.visible = true;
                }
            }
        }
        Rectangle {
            id: rect_random
            anchors.top: rect_restore.bottom
            anchors.topMargin: header_line
            anchors.left: rect_restore.left
            //anchors.leftMargin: default_margin
            width: parent.width / 10
            height: parent.height / 4
            Text {
                text: "random"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_random
                anchors.fill: parent
                onClicked: {
                    console.log("random!");
                    we1.url = getRandomUrl();
                    right_pane.visible = false;
                }
            }
        }

        Rectangle {
            id: rect_defaultLeft
            anchors.top: rect0.top
            anchors.topMargin: header_line
            anchors.left: rect_seperate1.right
            anchors.leftMargin: default_margin
            width: deault_rect_width
            height: deault_rect_height
            color: ma_defaultL.pressed ? "yellow" : "white"
            Text {
                text: config_left_name
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_defaultL
                anchors.fill: parent
                onClicked: {
                    we1.url = config_left_url
                }
            }
        }
        Rectangle {
            id: rect_defaultRight
            anchors.top: rect0.top
            anchors.topMargin: header_line
            anchors.left: rect_defaultLeft.right
            anchors.leftMargin: default_margin
            width: deault_rect_width
            height: deault_rect_height
            color: ma_defaultR.pressed ? "yellow" : "white"
            Text {
                text: config_right_name
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_defaultR
                anchors.fill: parent
                onClicked: {
                    we2.url = config_right_url
                }
            }
        }


        Rectangle {
            id: rect_google
            anchors.top: rect0.top
            anchors.topMargin: header_line
            anchors.left: rect_seperate2.right
            anchors.leftMargin: default_margin
            width: deault_rect_width
            height: deault_rect_height
            color: ma_google.pressed ? "yellow" : "white"
            Text {
                text: "google map"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_google
                anchors.fill: parent
                onClicked: {
                    we1.url = googlemap_page
                }
            }
        }

        Rectangle {
            id: rect_weather
            anchors.top: rect0.top
            anchors.topMargin: header_line
            anchors.left: rect_google.right
            anchors.leftMargin: default_margin
            width: deault_rect_width
            height: deault_rect_height
            color: ma_weather.pressed ? "yellow" : "white"
            Text {
                text: "y!weather"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            MouseArea {
                id: ma_weather
                anchors.fill: parent
                onClicked: {
                    we2.url = yweather_page
                }
            }
        }
    }


    Rectangle {
        id: lower_pane
        border.width: 2
        border.color: "red"
        color: "darkgrey"
        anchors.top: rect0.bottom
        width: parent.width
        height: parent.height

        Rectangle {
            id: left_pane
            width: parent.width * one_half
            height: parent.height
            anchors.left: parent.left
            anchors.right: right_pane.left
            color: "black"
            // border.width: 2
            // border.color: "blue"

            Text {
                id: we1_text
                anchors.left: parent.left
                anchors.leftMargin: default_margin
                anchors.top: parent.top
                width: parent.width
                height: deault_rect_height
                text: we1.url
                color: "white"
            }

            WebEngineView {
                id: we1
                width: parent.width
                height: parent.height - deault_rect_height
                anchors.top: we1_text.bottom
                anchors.left: parent.left

                url: siriwave_page
                onCertificateError: {
                    error.ignoreCertificateError()
                }
            }
        }

        Rectangle {
            id: right_pane
            width: visible ? parent.width * one_half : 0
            height: parent.height
            x: visible ? parent.width * one_half : parent.width
            color: "black"
            // border.width: 2
            // border.color: "green"

            Text {
                id: we2_text
                anchors.left: parent.left
                anchors.leftMargin: default_margin
                anchors.top: parent.top
                width: parent.width
                height: deault_rect_height
                text: we2.url
                color: "white"
            }
            WebEngineView {
                id: we2
                width: parent.width
                height: parent.height
                anchors.top: we2_text.bottom

                url: dnamusic_page
                onCertificateError: {
                    error.ignoreCertificateError()
                }
            }
        }


    }


}
