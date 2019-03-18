QT += core
QT -= gui

CONFIG += c++11

TARGET = carinfo
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    carvalue.cpp

HEADERS += \
    carvalue.h

INCLUDEPATH = /usr/local/include

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

use_qtlib {
    INCLUDEPATH += $${PWD}/../qtlib
    LIBS += -L/usr/local/lib -lqtlib
    DEFINES += USE_QTLIB
} else {
    INCLUDEPATH += $${PWD}/../qtlib
    SOURCES += $${PWD}/../qtlib/trypath.cpp
    HEADERS += $${PWD}/../qtlib/trypath.h
}
