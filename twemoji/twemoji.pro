QT += core
QT += gui
QT += qml

CONFIG += c++11

TARGET = twemoji
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

RESOURCES += \
    qml.qrc \
    emoji.qrc

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += emojicore.cpp \
    seq/seqcore.cpp

HEADERS += emojicore.h \
    seq/seqcore.h

win32 {
INCLUDEPATH += $$PWD/../../json/single_include
}
