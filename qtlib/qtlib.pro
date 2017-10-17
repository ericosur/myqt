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
HEADERS += commonutil.h \
    trypath.h
SOURCES += commonutil.cpp \
    trypath.cpp

### md5sum and sha1hmac
HEADERS += pass.h
SOURCES += pass.cpp

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
