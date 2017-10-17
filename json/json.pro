QT += core
QT -= gui

CONFIG += c++11

TARGET = json
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    trypath.cpp \
    util.cpp \
    utilvars.cpp \
    commonutil.cpp

HEADERS += \
    trypath.h \
    util.h \
    utilvars.h \
    commonutil.h

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson
