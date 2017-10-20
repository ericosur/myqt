TEMPLATE = app

QT += qml quick
QT += webengine
CONFIG -= app_bundle

SOURCES += main.cpp

SOURCES += core.cpp
HEADERS += core.h

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

RESOURCES += qml.qrc
DEFINES += DEFAULT_CONFIG_FILE=\\\"setting.json\\\"


INCLUDEPATH += $$PWD/../qtlib
DEPENDPATH  += $$PWD/../qtlib
LIBS += -L/usr/local/lib
LIBS += -lqtlib
