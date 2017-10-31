QT += core
QT -= gui

CONFIG += c++11

TARGET = b64
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += foo.cpp \
    testz.cpp \
    gettz.cpp \
    gtz.cpp \
    testmm.cpp \
    commontest.cpp \
    util.cpp

HEADERS += foo.h \
    testz.h \
    gettz.h \
    testmm.h \
    commontest.h \
    util.h

SOURCES += readi.cpp
HEADERS += readi.h

SOURCES += devinfo.cpp
HEADERS += devinfo.h

# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
