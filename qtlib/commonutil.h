#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

#include <stdio.h>
#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDebug>

bool writeStringToFile(const QString& str, const QString& fn);
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn);

#endif  // __COMMON_UTIL_H__
