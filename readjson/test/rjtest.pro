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
    foobar.cpp \
    hashtest.cpp \
    ../readjson.cpp \
    ../fileutil.cpp \

HEADERS += \
    test.h \
    foobar.h \
    ../readjson.h \
    ../fileutil.h


#LIBS += -L/usr/local/lib
#LIBS += -lqtlib
