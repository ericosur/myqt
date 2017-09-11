QT += core
QT -= gui

CONFIG += c++11

TARGET = usefunc
CONFIG += console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -Werror

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp
