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
    TEST_DEFAULT = 0xA000,
    TEST_DIRSEARCH = 0x10000,
    TEST_PERCENTENCODING,
    TEST_LOCALTIME,
    TEST_RUNSCRIPT,
    TEST_READCONF
} TestCategory;

class ConfigVar
{
public:
    bool bDebug = false;
    TestCategory kTest = TEST_DEFAULT;
    QString sTest;
};

extern ConfigVar gVars;

#endif  // __JSON__UTIL_H__
