#include "fileutil.h"

// #include <stdio.h>
// #include <string.h>

#include <QDebug>
#include <QCryptographicHash>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegExp>
#include <QRegularExpression>

// static member function
QString FileUtil::removeFilePrefix(const QString& fn)
{
    QString _fn = fn;
    _fn = _fn.remove("file://", Qt::CaseInsensitive);
    return _fn;
}

//due to fileURL will change ` to %60 , we need to cover the string , let file can be match in playlist.
//for example: file name is I`m Not a Girl.mp3
//fileURL for media browser will be I%60m Not a Girl.mp3
QString FileUtil::decodePercent(const QString name)
{
    QString s = name;
    QRegularExpression re("(%([A-Fa-f0-9][A-Fa-f0-9]))");
    QRegularExpressionMatchIterator i = re.globalMatch(s);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString all = match.captured(1);
        QString key = match.captured(2);
        bool ok;
        int _hex = key.toInt(&ok, 16);
        if (ok) {
            char value = (char)_hex;
            QString after = QString(value);
            s.replace(all, after);
        }
    }
    return s;
}

// static member function
QString FileUtil::getHashedFilename(const QString& fn)
{
    QString nfn = FileUtil::removeFilePrefix(fn);
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(nfn.toStdString().c_str(), nfn.length());
    QString result = hash.result().toHex().data();
    return QString("/tmp/") + result + QString(".png");
}

bool FileUtil::isDir(const QString& furl)
{
    QString ifn = FileUtil::removeFilePrefix(furl);
    QFileInfo pathFileInfo(ifn);
    return pathFileInfo.isDir();
}

bool FileUtil::isDirExist(const QString &url)
{
    QString ifn = FileUtil::removeFilePrefix( url );
    QDir dir(ifn);
    return dir.exists();
}

bool FileUtil::isUrlExist(const QUrl& url)
{
    bool res = false;
    //qDebug() << "filereader::exists? " << url;
    //qDebug() << "filereader::exists(): " << url.toLocalFile();
    if ( (res = url.isValid()) == true ) {
        //QString ifn = FileUtil::removePrefix(furl);
        res = QFileInfo::exists(url.toLocalFile());
    }
    //qDebug() << "filereader: " << (res?"ture":"false");
    return res;
}

bool FileUtil::isFileExist(const QString& fn)
{
    QString _fn = FileUtil::removeFilePrefix(fn);
    return QFileInfo::exists(_fn);
}

QString FileUtil::getBasename(const QString& fn)
{
    QString _fn = FileUtil::removeFilePrefix(fn);
    int index = _fn.lastIndexOf("/");
    if (index < 0) {
        return QString();
    }
    //qDebug() << "index:" << index;
    return _fn.right(_fn.length() - index - 1);
}

QString FileUtil::getPathname(const QString& fn)
{
    QString _fn = FileUtil::removeFilePrefix(fn);
    int index = _fn.lastIndexOf("/");
    if (index < 0) {
        return QString();
    }
    return _fn.left(index+1);
}

bool FileUtil::mkdir(const QString& foldername)
{
    if (!FileUtil::isDirExist(foldername)) {
        QDir().mkdir(foldername);
        return true;
    }
    return false;
}
