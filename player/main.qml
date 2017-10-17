import QtQuick 2.5
import QtQuick.Window 2.2
import com.rasmus 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "darkgrey"

    Component.onCompleted: {
        console.log("NoshDefine.CD_START: " + NoshDefine.CD_START);
        console.log("NoshDefine.ED_THREE: " + NoshDefine.ED_THREE);
        console.log("NoshDefine.MD_BALL: " + NoshDefine.MD_BALL);
    }

    // MouseArea {
    //     id: ma_all
    //     anchors.fill: parent
    //     onClicked: {
    //         console.log("NoshDefine.CD_START" + NoshDefine.CD_START);
    //     }
    // }

}
