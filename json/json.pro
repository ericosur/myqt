QT += core
QT -= gui

CONFIG += c++11

TARGET = json
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    trypath.cpp \
    util.cpp

HEADERS += \
    trypath.h \
    util.h

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson
