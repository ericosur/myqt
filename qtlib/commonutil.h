#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDebug>

#include <QTime>
#include <QCoreApplication>

#include <stdio.h>
#include <iostream>

bool writeStringToFile(const QString& str, const QString& fn);
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn);
bool readFileToByteArray(QByteArray& arr, const QString& fn);

#if QT_VERSION >= 0x050500
extern bool g_messageVerbose;
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
#endif

#endif  // __COMMON_UTIL_H__
