TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    filereader.cpp

RESOURCES += qml.qrc \
    yaqml.qrc

mac {
    QMAKE_MAC_SDK = macosx10.14
    CONFIG -= app_bundle
}

# Additional import path used to resolve QML modules in Qt Creator code model
QML_IMPORT_PATH =

HEADERS += \
    mytranslation.hpp \
    filereader.h

lupdate_only {
    SOURCES += main.qml MainForm.ui.qml
}

TRANSLATIONS = \
    lang_zh_TW.ts \
    lang_en_US.ts \
    lang_fr_FR.ts \
    lang_ar_AR.ts

DISTFILES +=
