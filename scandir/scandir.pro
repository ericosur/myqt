QT += core
QT -= qui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = scandir
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.12
DEFINES += MACOSX_DEPLOYMENT_TARGET=10.12

SOURCES += \
    main.cpp

SOURCES += \
    core.cpp \
    travelthread.cpp \
    idhash.cpp \
    miscutil.cpp

HEADERS += \
    core.h \
    travelthread.h \
    idhash.h \
    miscutil.h

