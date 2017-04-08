/// \file testmsg.h
///

#ifndef __TEST_MSG_H__
#define __TEST_MSG_H__

#include <QString>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

#define STRMSGINI    "strdef.ini"

QString findFileLocation(const QString& fn);
QString getmsg(const QString& locale_name, int id);

#endif // __TEST_MSG_H__
