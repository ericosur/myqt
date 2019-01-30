TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    nowplaycore.cpp \
    myimageprovider.cpp \
    pollthread.cpp \
    ../readjson.cpp \
    ../fileutil.cpp

HEADERS += \
    nowplaycore.h \
    myimageprovider.h \
    pollthread.h \
    ../readjson.h \
    ../fileutil.h

INCLUDEPATH += $${PWD}/../
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
