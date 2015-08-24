TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    Id3Tag.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Id3Tag.h

# taglib
CONFIG += localtaglib
CONFIG(localtaglib) {
    macx {
        INCLUDEPATH += /Users/ericosur/taglib/include/taglib
        LIBS += -L/Users/ericosur/taglib/lib
    } else {
        INCLUDEPATH += /home/rasmus/taglib/include/taglib
        LIBS += -L/home/rasmus/taglib/lib
    }
} else {
    INCLUDEPATH += /usr/include/taglib
}
LIBS += -ltag
