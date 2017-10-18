QT += core
QT -= gui

CONFIG += c++11

TARGET = json
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    util.cpp \
    utilvars.cpp

HEADERS += \
    util.h \
    utilvars.h \
    json.hpp

SOURCES += \
    testparsestring.cpp

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib
