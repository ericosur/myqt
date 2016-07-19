TEMPLATE = app

QT += qml quick

CONFIG += c++11
CONFIG += use_util

SOURCES += main.cpp \
    mydatasource.cpp

HEADERS += \
    mydatasource.h

use_util {
HEADERS += \
    ../util/msgqdef.h \
    ../util/yosemsg.h \
    ../util/shmdef.h \
    ../util/yoseshm.h
SOURCES += \
    ../util/yosemsg.cpp \
    ../util/yoseshm.cpp
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
