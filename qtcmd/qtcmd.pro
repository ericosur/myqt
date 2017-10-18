QT += core
QT -= qui

TARGET = qtcmd
TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp
HEADERS += wait.h

SOURCES += \
    testutil.cpp \
    jsonutil.cpp
HEADERS += \
    testutil.h \
    jsonutil.h

SOURCES += getlink.cpp

INCLUDEPATH += $$PWD/../qtlib
DEPENDPATH  += $$PWD/../qtlib

LIBS += -L/usr/local/lib
LIBS += -lqtlib
