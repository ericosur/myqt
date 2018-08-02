QT += core
QT -= gui

CONFIG += c++11

TARGET = cfgjson
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=   \
    main.cpp \
    readjson.cpp \
    getradioconfig.cpp

HEADERS += \
    readjson.h \
    getradioconfig.h

