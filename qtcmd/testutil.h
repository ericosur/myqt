#ifndef __UTIL_H__
#define __UTIL_H__

#include <QString>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>


#define CHECK_IF_DEBUG(x)   \
    if (gVars.bDebug) { \
        x; \
    }

bool handleOpt(int argc, char** argv);
void print_help();


typedef enum TestCategory {
    TC_DEFAULT = 0xA000,
    TC_MD5LISTTEST,
    TC_MD5SUMTEST,
    TC_SHA1SUMTEST,
    TC_HMACTEST,
    TC_ARRAYTEST,
} TestCategory;

class ConfigVar
{
public:
    bool bDebug = false;
    TestCategory kTest = TC_DEFAULT;
    int iCount = 0;
    QString sTeststring;
    QString sKeystring;
};

extern ConfigVar gVars;

#endif  // __JSON__UTIL_H__
