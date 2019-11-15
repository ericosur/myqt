import QtQuick 2.6

Item {
    id: _carplay_roundabout
    width:  500
    height: 500
    visible: true

    readonly property int m: 310
    readonly property int n: 266
    readonly property int a: 120
    readonly property int b: 74
    readonly property int qm: 300
    readonly property int qn: 276
    readonly property int qa: 180
    readonly property int qb: 128

    property double heading: 180.0
    property var degrees: [180]

    Timer {
        id: demo_timer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            //console.log('demo_timer onTriggered');

            degrees = [];
            var max_exit = 4
            for (var i = 0; i < max_exit; ++i) {
                if (randint(100) > 50) {
                    degrees.push(25 * randint(6));
                } else {
                    degrees.push(-20 * randint(6));
                }

            }
            // if drive by right side
            root.exitDeg = degrees.pop();
            degrees.push(root.exitDeg);
            degrees.push(180);
            root.arcBegin = root.exitDeg;  //Math.min(...degrees);
            root.arcEnd = 180; //Math.max(...degrees);
            //console.log('begin: ' + root.arcBegin + ' end: ' + root.arcEnd);
        }
    }

    Component.onCompleted: {
        demo_timer.running = false; // change to true to see the demo
        root.isJunction = true;
        root.isRoundabout = !root.isJunction;
        root.size = 300;
    }

    function rad2deg(rad) {
        return rad * 180.0 / Math.PI;
    }

    function deg2rad(deg) {
        return deg * Math.PI / 180.0;
    }

    function circle_x(x, y, r, deg) {
        var p = x + r * Math.cos(deg2rad(deg));
        return p;
    }
    function circle_y(x, y, r, deg) {
        var p = y + r * Math.sin(deg2rad(deg));
        return p;
    }

    // return: 0 ~ x-1
    function randint(x) {
        return Math.floor(Math.random()*x);
    }
    function get_angle(ang) {
        var is_inc = randint(2);
        var delta_angle = 0;

        if (randint(100)==1) {
            delta_angle = 90;
        } else {
            delta_angle = (randint(10)+1) * ((randint(6)==1)?4:1);
        }
        if (is_inc) {
            ang += delta_angle;
        } else {
            ang -= delta_angle;
        }

        if (ang < 0) {
            ang += 360;
        }
        if (ang >= 360) {
            ang -= 360;
        }
        return ang;
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "black"
    }

    // Image {
    //     id: ivi_display_clock_second
    //     anchors.centerIn: parent
    //     width: 12
    //     height: 93
    //     source: "./clock/second.png"
    //     transform: Rotation {
    //         id: secondRotation
    //         origin.x: 5.5; origin.y: 24.5;
    //         angle: heading * 6 + 180
    //         Behavior on angle {
    //             SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
    //         }
    //     }
    // }

    Item {
        id: root

        anchors.centerIn: parent
        width: size
        height: size

        property bool isJunction: false
        property bool isRoundabout: false
        property int exitDeg: 180
        //property real exitRad: deg2rad(exitDeg)

        property int size: 200               // The size of the circle in pixel
        property real arcBegin: 0            // start arc angle in degree
        property real arcEnd: 270            // end arc angle in degree
        property real arcOffset: 0           // rotation
        property real lineWidth: 20          // width of the line
        property string colorCircle: "#fcc226" //"#CC3333"
        property string colorBackground: "#779933"

        property alias beginAnimation: animationArcBegin.enabled
        property alias endAnimation: animationArcEnd.enabled

        property int animationDuration: 200

        onArcBeginChanged: canvas.requestPaint()
        onArcEndChanged: canvas.requestPaint()

        Behavior on arcBegin {
           id: animationArcBegin
           enabled: false
           NumberAnimation {
               duration: root.animationDuration
               easing.type: Easing.InOutCubic
           }
        }

        Behavior on arcEnd {
           id: animationArcEnd
           enabled: false
           NumberAnimation {
               duration: root.animationDuration
               easing.type: Easing.InOutCubic
           }
        }

        Canvas {
            id: canvas
            anchors.fill: parent
            rotation: -90 + parent.arcOffset

            onPaint: {
                var ctx = getContext("2d")
                var x = width / 2
                var y = height / 2
                var start = Math.PI * (parent.arcBegin / 180)
                var end = Math.PI * (parent.arcEnd / 180)
                ctx.reset()

                var line_length = 40;
                var line_width = 20;
                var line_padding = 30;
                var arc_padding = deg2rad(5);

                if (root.isJunction) {
                    degrees.forEach(myFunction);
                }

                if (root.isRoundabout) {
                    // draw exit
                    degrees.forEach(drawExit);

                    ctx.lineWidth = root.lineWidth
                    // background circle
                    var r = width / 2 - parent.lineWidth / 2 - line_length
                    ctx.beginPath();
                    ctx.arc(x, y, r, 0, Math.PI * 2, false) // full circle
                    ctx.strokeStyle = root.colorBackground
                    ctx.stroke()

                    // foreground circle
                    ctx.beginPath();
                    ctx.arc(x, y, r, start-arc_padding, end+arc_padding, false)
                    ctx.strokeStyle = root.colorCircle
                    ctx.stroke()
                }

                function myFunction(item, index) {
                    var tail_length = 8;
                    var x1 = circle_x(x, y, tail_length, item+180);
                    var y1 = circle_y(x, y, tail_length, item+180);
                    var x2 = circle_x(x, y, x-line_padding, item);
                    var y2 = circle_y(x, y, y-line_padding, item);
                    ctx.beginPath();
                    ctx.moveTo(x1, y1);
                    ctx.lineTo(x2, y2);
                    ctx.lineWidth = line_width
                    if (item == root.exitDeg || item == 180) {
                        ctx.strokeStyle = root.colorCircle
                    } else {
                        ctx.strokeStyle = root.colorBackground
                    }
                    ctx.stroke()
                }

                function drawExit(item, index) {
                    var r1 = width/2 - parent.lineWidth/2 - line_length;
                    var x1 = circle_x(x, y, r1, item);
                    var y1 = circle_y(x, y, r1, item);
                    var r2 = r1 + line_padding * 1.5;
                    var x2 = circle_x(x, y, r2, item);
                    var y2 = circle_y(x, y, r2, item);
                    ctx.beginPath();
                    ctx.moveTo(x1, y1);
                    ctx.lineTo(x2, y2);
                    ctx.lineWidth = line_width;
                    if (item == root.exitDeg || item == 180) {
                        ctx.strokeStyle = root.colorCircle;
                    } else {
                        ctx.strokeStyle = root.colorBackground;
                    }

                    ctx.stroke();
                }
            }
        }
    }


}
