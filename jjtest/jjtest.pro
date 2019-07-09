TARGET = jjtest
TEMPLATE = app

QT += core
QT -= gui

CONFIG += debug
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG += sdk_no_version_check

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp
SOURCES += json_parse_test.cpp

SOURCES += \
    foo.cpp \
    bar.cpp
HEADERS += \
    foo.h \
    bar.h

# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib

# readjson
INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

INCLUDEPATH += /usr/local/include
