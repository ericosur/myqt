QT += core gui
QT += widgets

TARGET = testtool
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

mac {
    QMAKE_MAC_SDK = macosx10.14
    CONFIG -= app_bundle
}
