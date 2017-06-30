QT += core
QT -= gui

CONFIG += c++11

TARGET = json
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    readjson.cpp \
    trypath.cpp \
    util.cpp

HEADERS += \
    readjson.h \
    trypath.h \
    util.h

