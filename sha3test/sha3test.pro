QT += core dbus
QT -= qui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = sha3test
TEMPLATE = app

SOURCES += main.cpp \
    readthread.cpp \
    core.cpp

HEADERS += \
    readthread.h \
    core.h

INCLUDEPATH += $$PWD/../qtlib
INCLUDEPATH += $$PWD/../readjson

DEPENDPATH  += $$PWD/../qtlib

LIBS += -L/usr/local/lib
LIBS += -lqtlib
LIBS += -lreadjson

mac {
    QMAKE_MAC_SDK = macosx10.14
    CONFIG -= app_bundle
}
