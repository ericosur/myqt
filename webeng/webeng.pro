TEMPLATE = app

QT += qml quick
QT += webengine

SOURCES += main.cpp

SOURCES += core.cpp \
    commonutil.cpp
HEADERS += core.h \
    commonutil.h

INCLUDEPATH += $${PWD}/../readjson
LIBS += -L/usr/local/lib -lreadjson

RESOURCES += qml.qrc
DEFINES += DEFAULT_CONFIG_FILE=\\\"setting.json\\\"


INCLUDEPATH += $$PWD/../qtlib
DEPENDPATH  += $$PWD/../qtlib
LIBS += -L/usr/local/lib
LIBS += -lqtlib
