#ifndef __MISC_UTIL_H__
#define __MISC_UTIL_H__

#include <QtGlobal>

void msgHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg);
bool handleOpt(int argc, char** argv);
QString md5sum(const char* buffer, int size);
bool isFileExisted(const QString& fn);
int send_msgq(int key, int type, const char* str);

extern bool bDebug;

#endif  // __MISC_UTIL_H__
