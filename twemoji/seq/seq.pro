QT += core
QT += gui
QT += qml

CONFIG += c++11

TARGET = seq
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += seqcore.cpp

HEADERS += seqcore.h

