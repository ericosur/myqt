#ifndef __JSON__UTIL_H__
#define __JSON__UTIL_H__

#include <QDebug>
#include <unistd.h>
#include <stdio.h>

#define DEFAULT_OUTPUT_FN   "/tmp/a.json"
#define JSONFILE "a.json"
#define CITYNAME "taipei"

extern bool gSelectAll;
extern bool gDebug;

void writeStringToFile(const QString& str, const QString& fn);
bool handleOpt(int argc, char** argv);

#endif  // __JSON__UTIL_H__
