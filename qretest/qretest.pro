QT += core
QT -= gui

CONFIG += c++11
QMAKE_MAC_SDK = macosx10.11
TARGET = qretest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp