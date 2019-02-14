TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    core.cpp \
    ../readjson.cpp \
    ../fileutil.cpp

HEADERS += \
    core.h \
    ../readjson.h \
    ../fileutil.h

INCLUDEPATH += $${PWD}/../
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
