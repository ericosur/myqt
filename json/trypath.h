#ifndef __TRY_PATH_H__
#define __TRY_PATH_H__

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDebug>


QString getHomepath();
bool searchFileFromList(const QStringList& _list, const QString& _file, QString& result);

#endif  // __TRY_PATH_H__
