#include "gettz.h"

// input: "/usr/share/timezone/zoneinfo/Asia/Tehran"
// seperator: "zoneinfo/"
// output: "Asia/Tehran"
QString getRhsOf(const QString& input, const QString& seperator)
{
    QString result;
    if (input.length()) {
        int i = input.indexOf(seperator);
        if ( i < 0) {
            result = "";
        } else {
            result = input.right(input.length() - i - seperator.length());
        }
    }
    qDebug() << Q_FUNC_INFO << result;
    return result;
}


// on target, most timezone name are not defined
//            just take rhs part and return true
// on host, timezone names are well defined,
//          will use QTimeZone to check
bool hasPathValidTz(const QString& test, QString& rhs)
{
    rhs = getRhsOf(test, "zoneinfo/");
#if __arm__
    return true;
#else
    QTimeZone tz(rhs.toUtf8());
    return tz.isValid();
#endif
}

// start from /etc/localtime
// if succeed, will get time zone name like "Asia/Dubai"
QString getTimeZoneNameFromLink()
{
#define LOCALTIME_PATH  "/etc/localtime"
    bool bVerbose = false;

    QString testpath = LOCALTIME_PATH;
    QString result;

    do {
        QFileInfo info(testpath);
        if (bVerbose) qDebug() << "test on:" << info.filePath();
        if ( !info.exists() ) {
            if (bVerbose) qWarning() << "not exist";
            break;
        }
        if (!info.isSymLink()) {
            if (bVerbose) qDebug() << "not symlink:" << info.filePath();
            result = testpath;
            break;
        } else {
            testpath = QFile::symLinkTarget(testpath);
            if (bVerbose) qDebug() << "link to:" << testpath;
#ifndef __arm__
            QString rhs;
            if ( hasPathValidTz(testpath, rhs) )
                return rhs;
#endif
        }
    } while (true);

    QString rhs;
    if ( hasPathValidTz(result, rhs) ) {
        return rhs;
    } else {
        return "";
    }
}
