QT += core
QT -= qui

TARGET = qfile
TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
  ini.c \
  INIReader.cpp \
  cfgutil.cpp

HEADERS  += \
  ini.h \
  INIReader.h \
  cfgutil.h



