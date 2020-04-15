TARGET = loadapn
TEMPLATE = app

QT += core
QT -= gui

CONFIG += debug
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG += sdk_no_version_check

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += \
    testload.cpp
HEADERS += \
    testload.h

RESOURCES += qml.qrc
