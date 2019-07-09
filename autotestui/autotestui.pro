QT += core gui
QT += widgets

TARGET = autotestui
TEMPLATE = app

CONFIG += readjson


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
