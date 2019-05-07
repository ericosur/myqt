TARGET = strwidth
TEMPLATE = app

QT += qml quick widgets

CONFIG += debug
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG += sdk_no_version_check

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += wordutil.cpp
HEADERS += wordutil.h


# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib

# readjson
INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

INCLUDEPATH += /usr/local/include
