QT += core
QT -= gui

TARGET = qset
TEMPLATE = app
CONFIG += c++11
CONFIG += console

CONFIG += use_jsonhpp

mac {
#CONFIG+=sdk_no_version_check
    QMAKE_MAC_SDK = macosx10.14
    CONFIG -= app_bundle
}


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
