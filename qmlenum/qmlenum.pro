QT += qml quick widgets

CONFIG += c++11

TARGET = qmlenum
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

RESOURCES += qml.qrc

SOURCES += main.cpp

HEADERS += rcommon.h
SOURCES += rcommon.cpp
