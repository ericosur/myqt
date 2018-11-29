QT += core
QT -= gui

CONFIG += c++11

TARGET = jjtest
CONFIG += console
CONFIG -= app_bundle
CONFIG+=sdk_no_version_check

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += foo.cpp
HEADERS += foo.h

SOURCES += json_parse_test.cpp

# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib

# readjson
INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

INCLUDEPATH += /usr/local/include
