QT += core
QT -= gui

TARGET = qset
TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

CONFIG += use_jsonhpp

QMAKE_MAC_SDK = macosx10.11

SOURCES += main.cpp\
    core.cpp \
    mythreads.cpp

HEADERS  += \
    core.h \
    mythreads.h

INCLUDEPATH += $$PWD/../qtlib
DEPENDPATH  += $$PWD/../qtlib
LIBS += -L/usr/local/lib
LIBS += -lqtlib


use_jsonhpp {
    DEFINES += USE_JSONHPP
    INCLUDEPATH += /usr/local/include
}
