QT += core
QT -= qui

TARGET = rjtest
TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

SOURCES += \
    test.cpp \
    ../readjson.cpp

HEADERS += \
    test.h \
    ../readjson.h


#LIBS += -L/usr/local/lib
#LIBS += -lqtlib
