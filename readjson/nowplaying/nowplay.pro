TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    npcore.cpp \
    myimageprovider.cpp \
    pollthread.cpp \
    ../readjson.cpp

HEADERS += \
    npcore.h \
    myimageprovider.h \
    pollthread.h \
    ../readjson.h

INCLUDEPATH += $${PWD}/../
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
