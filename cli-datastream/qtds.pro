QT += core
QT -= gui
CONFIG += c++11
TARGET = qtds
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

HEADERS += \
    mymap.h

SOURCES += main.cpp \
    mymap.cpp

# qtlib
INCLUDEPATH += $${PWD}/../qtlib
LIBS += -L/usr/local/lib -lqtlib
