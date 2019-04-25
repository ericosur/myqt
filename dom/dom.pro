QT += core
QT += gui
QT += xml
QT += qml
QT += svg

CONFIG += c++11

TARGET = dom
CONFIG += console
CONFIG -= app_bundle
CONFIG += sdk_no_version_check

TEMPLATE = app

QMAKE_CXXFLAGS += -Werror
QMAKE_CXXFLAGS += -Wextra

SOURCES += main.cpp

SOURCES += \
    core.cpp \
    domutil.cpp

HEADERS += \
    core.h \
    domutil.h

INCLUDEPATH += /usr/local/include
INCLUDEPATH += $${PWD}/../readjson

LIBS += -L/usr/local/lib -lreadjson

RESOURCES += qml.qrc
