QT += core
QT -= gui

CONFIG += c++11

TARGET = json
CONFIG += console
CONFIG -= app_bundle
CONFIG+=sdk_no_version_check

TEMPLATE = app

SOURCES += main.cpp \
    util.cpp \
    utilvars.cpp

HEADERS += \
    util.h \
    utilvars.h

SOURCES += \
    testparsestring.cpp

SOURCES += \
    getmsg.cpp

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib

INCLUDEPATH += /usr/local/include
