QT -= gui
QT += core
CONFIG += c++11
CONFIG += shared

TARGET = readjson
TEMPLATE = lib
VERSION = 1.0.0

SOURCES += readjson.cpp \
    fileutil.cpp

HEADERS += readjson.h \
    fileutil.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
