/**
    \file commonutil.h
    \brief provides some common utility function here

**/

#ifndef __COMMONUTIL_H__
#define __COMMONUTIL_H__

#include <QTime>
#include <QCoreApplication>

extern bool g_messageVerbose;
// customized message handler
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif  // __COMMONUTIL_H__
