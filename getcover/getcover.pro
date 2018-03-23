QT += core gui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = getcover
TEMPLATE = app

# my own extra config
CONFIG += use_qtlib
CONFIG += use_localtaglib

QMAKE_MAC_SDK = macosx10.12
DEFINES += MACOSX_DEPLOYMENT_TARGET=10.11

HEADERS += getcover.h \
    yoseshm.h \
    handleopt.h \
    worker.h \
    core.h

SOURCES += main.cpp \
    getcover.cpp \
    yoseshm.cpp \
    handleopt.cpp \
    worker.cpp \
    core.cpp

HEADERS += tbhash.h
SOURCES += tbhash.cpp

LIBS += -ltag
# taglib need libz
LIBS += -lz

use_localtaglib {
    linux {
        INCLUDEPATH += /usr/local/include
        LIBS += -L/usr/local/lib
    }
    macx {
        INCLUDEPATH += /opt/local/include
        LIBS += -L/opt/local/lib
    }
}

use_qtlib {
    DEFINE += USE_QTLIB
    INCLUDEPATH += $$PWD/../qtlib
    DEPENDPATH  += $$PWD/../qtlib
    LIBS += -L/usr/local/lib
    LIBS += -lqtlib
}
