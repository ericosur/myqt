/**
 * \file inireader.cpp
 */

#include "inireader.h"

IniReader* IniReader::_instance = nullptr;
IniReader* IniReader::getInstance()
{
    if (_instance == nullptr) {
        _instance = new IniReader();
    }
    return _instance;
}

IniReader::IniReader()
{
    bActive = init_reader();
}

bool IniReader::init_reader()
{
    if (!QFile::exists(DEFAULT_INI_PATH)) {
        qWarning() << "ini not found!";
        return false;
    }

    if (ini == nullptr) {
        ini = new QSettings(DEFAULT_INI_PATH, QSettings::IniFormat);
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        ini->setIniCodec(codec);
    }

    if (ini == nullptr) {
        qWarning() << "ini reader is not init'd";
        return false;
    }

    basefileid = ini->value("/thread/BASE_FILEID", -1).toInt();
    filecount = ini->value("/fileid/size", -1).toInt();

    if (basefileid < 0 || filecount < 0) {
        return false;
    }

    return true;
}

bool IniReader::startRead()
{
    return true;
}

QString IniReader::requestById(int id)
{
    if (!bActive || ini == nullptr) {
        return "null";
    }

    if (id < basefileid || id >= basefileid + filecount) {
        qWarning() << "out of bound!";
        return "null";
    }

    QString key = QString("/fileid/%1").arg(id);
    QString str = ini->value(key, "null").toString();
    return str;
}

QString IniReader::requestBySmallId(int id)
{
    return requestById(id + basefileid);
}
