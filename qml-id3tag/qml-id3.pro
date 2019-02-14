TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    id3tag.cpp \
    myimageprovider.cpp \
    myid3data.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)

HEADERS += \
    Id3Tag.h \
    myimageprovider.h \
    myid3data.h

# taglib
CONFIG(localtaglib) {
    macx {
        INCLUDEPATH += /Users/ericosur/taglib/include/taglib
        LIBS += -L/Users/ericosur/taglib/lib
    } else {
        INCLUDEPATH += /home/rasmus/taglib/include/taglib
        LIBS += -L/home/rasmus/taglib/lib
    }
}

INCLUDEPATH += $${PWD}/../readjson
LIBS += -lreadjson

INCLUDEPATH += /usr/include/taglib
INCLUDEPATH += /usr/local/include
LIBS += -ltag
