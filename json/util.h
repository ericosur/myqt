#ifndef __JSON__UTIL_H__
#define __JSON__UTIL_H__

#include <QString>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>

//#define DEFAULT_OUTPUT_FN   "/tmp/a.json"
#define DEFAULT_OUTPUT_FN   "/home/rasmus/src/myqt/json/all.json"
#define JSONFILE "a.json"
#define CITYNAME "taipei"

extern bool gSelectAll;
extern bool gDebug;
extern QString gFilename;

void writeStringToFile(const QString& str, const QString& fn);
bool handleOpt(int argc, char** argv);

#endif  // __JSON__UTIL_H__
