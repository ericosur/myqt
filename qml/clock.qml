import QtQuick 2.5

Rectangle {
    id: clock
    width: 148
    height: 148
    color: "black"

    property int hours
    property int minutes
    property int seconds
    property real shift: 0
    property bool isInternationalTime: false
    property bool isActive: true

    function timeChanged() {
        var date;

        date = new Date();
        hours = clock.isInternationalTime ? date.getUTCHours() + Math.floor(clock.shift) : date.getHours()
        minutes = clock.isInternationalTime ? date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
        seconds = clock.isInternationalTime ? date.getUTCSeconds() : date.getSeconds();
        ivi_display_clock_day.text = qsTr(date.getDate().toString());
    }

    Timer {
        interval: 100; running: clock.isActive; repeat: true;
        onTriggered: clock.timeChanged()
    }

    Image {
        id: ivi_display_clock_bg_active
        width: 148
        height: 148
        source: "./clock/clock_bg.png"

        Rectangle
        {
            x: 50
            y: 100
            width: 50
            height: 15
            color: "black"
        }

        Image {
            id: ivi_display_clock_hour_active
            x: 67
            y: 31
            width: 14
            height: 55
            source: "./clock/hour.png"
            transform: Rotation {
                  id: hourRotation
                  origin.x: 6.5; origin.y: 43.5;
                  angle: (clock.hours * 30) + (clock.minutes * 0.5)
                  Behavior on angle {
                      SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                  }
              }
        }

        Image {
            id: ivi_display_clock_mintue_active
            x: 67
            y: 71
            width: 14
            height: 69
            source: "./clock/minute.png"
            transform: Rotation {
                id: minuteRotation
                origin.x: 6.5; origin.y: 4;
                angle: clock.minutes * 6 + 180
                Behavior on angle {
                    SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                }
            }
        }

        Image {
            id: ivi_display_clock_second
            x: 68
            y: 51
            width: 12
            height: 93
            source: "./clock/second.png"
            transform: Rotation {
                id: secondRotation
                origin.x: 5.5; origin.y: 24.5;
                angle: clock.seconds * 6 + 180
                Behavior on angle {
                    SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                }
            }
        }

        Text {
            id: ivi_display_clock_day
            x: 104
            y: 66
            color: clock.isActive ? "#fcc226" : "#ffffff"
            text: "21"
            font.pixelSize: 10
            //font.family: fontRegular.name
        }
    }
}
