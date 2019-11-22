import QtQuick 2.0
import QtQml 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

ApplicationWindow {
    id: mainwindow
    title: "svg dom test"
    width: 640
    height: 480
    x: 100
    y: 0
    visible: true

    property string baseurl: core.basesvg
    property string exiturl: core.outsvg
    property int icon_size: 190

    Item {
        x: 0
        y: 0
        width: 800
        height: 400

        Text {
            id: base
            x: parent.x + 10
            y: parent.y + 10
            font.pixelSize: 16
            text: "hello world"
        }

        Rectangle {
            id: rect_bg
            x: 0
            y: 80
            width: parent.width
            height: parent.height - 80
            color: "black"

            Image {
                id: img0
                x: 200
                y: 20
                visible: true
                width: icon_size
                height: icon_size
                //source: "file:///home/rasmus/src/myqt/progresscircle/roundabout_base.svg"
                source: core.outpng
            }
            Image {
                x: img0.x + img0.width + 10
                y: img0.y
                visible: img0.visible
                height: icon_size
                width: icon_size
                //opacity: 0.8
                //source: "file:///home/rasmus/src/myqt/progresscircle/roundabout_right.svg"
                source: core.outsvg
            }

            Image {
                id: img_cmb
                x: 20
                y: 20
                width: icon_size
                height: icon_size
                source: core.basesvg
            }
            Image {
                x: img_cmb.x
                y: img_cmb.y
                width: icon_size
                height: icon_size
                source: core.outsvg
            }
        }
    }
}
