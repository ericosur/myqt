/// \file core.cpp

#include "core.h"

#define INI_PATH    "../playlist.ini"

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
}

void Core::start()
{
    read_ini(INI_PATH);
}

void Core::read_ini(const QString& fn)
{
    if (mIni == NULL) {
        mIni = new QSettings(fn, QSettings::IniFormat);
    }
    mIni->setIniCodec("UTF-8");
    QStringList sl = mIni->childGroups();
    for (int i=0; i<sl.size(); ++i) {
        qDebug() << "group:" << sl.at(i);
        mIni->beginGroup(sl.at(i));
        QStringList kl = mIni->childKeys();
        for (int j=0; j<kl.size(); ++j) {
            qDebug() << j << ":" << kl.at(j) << "==>"
                     << mIni->value(kl.at(j));
        }
        mIni->endGroup();
    }
}
