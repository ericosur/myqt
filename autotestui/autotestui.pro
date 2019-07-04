QT += core gui
QT += widgets

TARGET = autotestui
TEMPLATE = app

##### NOTE HERE #####
# turn on if build for target device
# turn off if build on ubuntu host
#CONFIG += USE_YOSETARGET
# if you open amis project from codebase no matter host/target build,
# the following part will handle automatically

message("product.sh found ==> HOST build")
CONFIG -= use_target
CONFIG += readjson

#message("product.sh not found ==> TARGET build")
#CONFIG += use_target


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS  += \
    mainwindow.h

FORMS    += mainwindow.ui

readjson {
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += $$PWD/../readjson
    SOURCES += \
        ../readjson/readjson.cpp \
        ../readjson/fileutil.cpp
    HEADERS += \
        ../readjson/readjson.h \
        ../readjson/fileutil.h
}

use_target {
    # define this if target build
    DEFINES += USE_YOSETARGET
    LIBS += -lhmi
}

mac {
    QMAKE_MAC_SDK = macosx10.14
    CONFIG -= app_bundle
}
