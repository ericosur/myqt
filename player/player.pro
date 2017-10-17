QT += core qml quick
#QT -= gui

CONFIG += c++11

TARGET = player
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

RESOURCES += qml.qrc

SOURCES += main.cpp

HEADERS += basicplayer.h \
    musicplayer.h \
    videoplayer.h \
    core.h

SOURCES += basicplayer.cpp \
    musicplayer.cpp \
    videoplayer.cpp \
    core.cpp

HEADERS += rcommon.h
SOURCES += rcommon.cpp

INCLUDEPATH += $$PWD/../qtlib
DEPENDPATH  += $$PWD/../qtlib
LIBS += -L/usr/local/lib
LIBS += -lqtlib
