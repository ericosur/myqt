#ifndef __UTIL_MSGOUT_H__
#define __UTIL_MSGOUT_H__

#include <QDebug>

extern bool g_messageVerbose;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif  // __UTIL_MSGOUT_H__
