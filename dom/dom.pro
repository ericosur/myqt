QT += core
QT += gui
QT += xml
QT += svg

CONFIG += c++11

TARGET = dom
CONFIG += console
CONFIG -= app_bundle
CONFIG+=sdk_no_version_check

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += domutil.cpp
HEADERS += domutil.h

INCLUDEPATH += /usr/local/include
