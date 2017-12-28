import QtQuick 2.5
import QtQuick.Window 2.2
import com.rasmus 2.0

Window {

    //property string abc: null
    property var foo

    visible: true
    width: 400
    height: 400
    x: 10; y:10
    title: qsTr("Hello World")
    color: "darkgrey"

    Component.onCompleted: {
        console.log("NoshDefine.CD_START: " + NoshDefine.CD_START);
        console.log("NoshDefine.ED_THREE: " + NoshDefine.ED_THREE);
        console.log("NoshDefine.MD_BALL: " + NoshDefine.MD_BALL);
        console.log("string: " + foo);
        if (foo == "") {
            console.log("empty");
        }
        if (foo == null) {
            console.log("null");
        }
        foo = "";
        console.log("string: " + foo);
        if (foo == "") {
            console.log("empty");
        }
        if (foo == null) {
            console.log("null");
        }

    }

    Rectangle {
        id: rect_test
        x: 10; y: 10
        width: 100
        height: 50
        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("pressed: " + rcommon.sayHello(NoshDefine.ED_THREE));
                console.log("pressed: " + rcommon.sayHello(NoshDefine.CD_RUNNING));
            }
        }
    }

}
