#ifndef __COMMON_FILE_UTIL_H__
#define __COMMON_FILE_UTIL_H__

#include <QString>
#include <QUrl>
#include <QDebug>

class FileUtil
{
public:
    /// in: "file:///data/app/abc.txt"
    /// out: "/data/app/abc.txt"
    static QString removeFilePrefix(const QString& fn);

    static QString decodePercent(const QString name);

    static bool isDir(const QString& furl);
    static bool isDirExist( const QString& url );
    static bool isUrlExist(const QUrl& url);
    static bool isFileExist(const QString& str);
    static QString getHashedFilename(const QString& fn);

    // get leftmost part as filename
    static QString getBasename(const QString& fn);
    // get path part with trailing '/''
    static QString getPathname(const QString& fn);

    static bool mkdir(const QString& foldername);
};

#endif // __COMMON_FILE_UTIL_H__
