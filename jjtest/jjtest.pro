QT += core
QT -= gui

CONFIG += c++11

TARGET = jjtest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += foo.cpp
HEADERS += foo.h


# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib
