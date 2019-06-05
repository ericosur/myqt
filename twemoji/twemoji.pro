QT += core
QT += gui
QT += qml

CONFIG += c++11

TARGET = twemoji
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += emojicore.cpp

HEADERS += emojicore.h

RESOURCES += \
    qml.qrc \
    emoji.qrc
