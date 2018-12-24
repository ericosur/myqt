/// \file residutil.h
///
/// it is former testmsg.h

#ifndef __LIBHMI_RESID_UTIL_H__
#define __LIBHMI_RESID_UTIL_H__

#include <QString>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

#define STRMSGINI           "strdef.ini"
#define STRMSG_JSONFILE     "strdef.json"

QString findFileLocation(const QString& fn);
QString getStringByIntid(const QString& locale_name, int id);

///
/// [IN] locale_name, eg: en_US, ar_AE
/// [IN] strid, eg: "stringid_helloworld"
///      so this function will lookup this strid from string table
///
QString getStringByStrid(const QString& locale_name, const QString& strid);
//QString getjsonmsg(const QString& locale_name, const QString& strid);

#endif // __LIBHMI_RESID_UTIL_H__
