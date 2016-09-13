QT += core dbus
QT -= qui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = getcover
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.11
DEFINES += MACOSX_DEPLOYMENT_TARGET=10.11

HEADERS += getcover.h \
    yoseshm.h
SOURCES += main.cpp \
    getcover.cpp \
    yoseshm.cpp

HEADERS += tbhash.h
SOURCES += tbhash.cpp

LIBS += -ltag

# add self-built taglib
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -ltag

# taglib need libz
LIBS += -lz

