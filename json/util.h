#ifndef __JSON__UTIL_H__
#define __JSON__UTIL_H__

#include <QString>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>

#include "utilvars.h"

//#define DEFAULT_OUTPUT_FN   "/tmp/a.json"
#define DEFAULT_OUTPUT_FN   "/home/rasmus/src/myqt/json/all.json"
#define JSONFILE "a.json"
#define CITYNAME "taipei"

#define CHECK_IF_DEBUG(x)   \
    if (UtilVars::getInstance()->bDebug) { \
        x; \
    }

bool writeStringToFile(const QString& str, const QString& fn);
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn);
bool handleOpt(int argc, char** argv);
void print_help();

#endif  // __JSON__UTIL_H__
