#ifndef __TEST_UTIL_H__
#define __TEST_UTIL_H__

#include <QString>
#include <QMap>
#include <QDebug>
#include <unistd.h>
#include <stdio.h>

#include "pass.h"

#define CHECK_IF_DEBUG(x)   \
    if (gVars.bDebug) { \
        x; \
    }

bool handleOpt(int argc, char** argv);
void print_help();

typedef QString (*pfHash)(const QString&);

QString get_one_string(int idx);
QString getHash(const QString& hashname, const QString& str);
QString get_md5sum(const QString& str);
QString get_sha1sum(const QString& str);
QString get_sha3sum(const QString& str);
void test_sha1hmac();

typedef enum TestCategory {
    TC_DEFAULT = 0xA000,
    TC_MD5LISTTEST,
    TC_MD5SUMTEST,
    TC_SHA1SUMTEST,
    TC_SHA3SUMTEST,
    TC_HMACTEST,
    TC_ARRAYTEST,
    TC_READCONFIG,
    TC_PROCESS,
} TestCategory;

class ConfigVar
{
public:
    bool bDebug = false;
    TestCategory kTest = TC_DEFAULT;
    int iCount = 0;
    QString sTeststring;
    QString sKeystring;
    QString sConfig;
};

extern ConfigVar gVars;

#endif  // __TEST_UTIL_H__
