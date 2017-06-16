QT += core dbus
QT -= qui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = sha3test
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.12
DEFINES += MACOSX_DEPLOYMENT_TARGET=10.12

SOURCES += main.cpp \
    pass.cpp \
    readthread.cpp \
    core.cpp

HEADERS += pass.h \
    readthread.h \
    core.h
