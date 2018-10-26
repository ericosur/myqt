QT += core
QT -= gui

CONFIG += c++11

TARGET = qcore
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    foothread.cpp \
    barcontrol.cpp

HEADERS += \
    foothread.h \
    barcontrol.h

HEADERS += filelock.h
SOURCES += filelock.cpp

# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib
