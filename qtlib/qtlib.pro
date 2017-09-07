#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T22:54:07
#
#-------------------------------------------------

QT -= gui
QT += core
CONFIG += c++11
CONFIG += shared

TARGET = qtlib
TEMPLATE = lib
VERSION = 1.0.1

SOURCES += retry.cpp
HEADERS += retry.h

### flock ###
HEADERS += flock.h
SOURCES += flock.cpp

### simple notify ###
HEADERS += simplenotify.h
SOURCES += simplenotify.cpp

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
