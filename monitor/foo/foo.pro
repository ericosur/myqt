TEMPLATE = app
TARGET = foobin
QT += core
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
QMAKE_MAC_SDK = macosx10.12

SOURCES += main.cpp

### FLOCK ###
INCLUDEPATH += $$PWD/../../qtlib
DEPENDPATH  += $$PWD/../../qtlib
LIBS += -lqtlib
LIBS += -L/usr/local/lib

### msgq ####
HEADERS += msgqsend.h
SOURCES += msgqsend.cpp
