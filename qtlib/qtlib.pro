QT -= gui
QT += core
CONFIG += c++11
CONFIG += shared

TARGET = qtlib
TEMPLATE = lib
VERSION = 1.0.2

SOURCES += retry.cpp
HEADERS += retry.h

### flock ###
HEADERS += flock.h
SOURCES += flock.cpp

### simple notify ###
HEADERS += simplenotify.h
SOURCES += simplenotify.cpp

### common util ###
HEADERS += commonutil.h
SOURCES += commonutil.cpp

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
