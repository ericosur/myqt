QT -= gui
QT += core
CONFIG += c++11
CONFIG += shared

TARGET = readjson
TEMPLATE = lib
VERSION = 1.0.0

SOURCES += readjson.cpp
HEADERS += readjson.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
