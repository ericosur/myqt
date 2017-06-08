#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QProcess>
#include <QDebug>

#include "foo.h"
#include "testz.h"
#include "readi.h"

#include "devinfo.h"

void gtz();

void test_runscript()
{
    QProcess process;
    process.start("mytestscript");
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    qDebug() << "stdout: " << stdout;
    qDebug() << "stderr: " << stderr;

    process.close();
}

bool try_path(const QString& _home, QDir& _dir)
{
#ifdef USE_TARGET
    QString dirpath = "/data";
#else
    QString dirpath = QString("%1/Dropbox/Music").arg(_home);
    //dirpath = QDir::fromNativeSeparators(dirpath);
#endif
    QDir dir( dirpath );
    if ( dir.exists() ) {
        _dir = dir;
        return true;
    }
    // 2nd try
    dirpath = QString("%1/Music").arg(_home);
    dir.setPath(dirpath);
    if ( dir.exists() ) {
        _dir = dir;
        return true;
    }
    return false;
}

void testdir(const QString& _home)
{
    QDir dir;
    if ( !try_path(_home, dir) ) {
        qWarning() << "no proper dir...";
        return;
    }

    Foo foo;
    QStringList filter;

    foo.clear();
    filter << "*.mp3" << "*.m4a" << "*.ape";
    int cnt = 0;

    foreach (QString file, dir.entryList(filter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullpath = _info.filePath();
        QString _encoded = QFile::encodeName(_fullpath);
        QUrl _url = QUrl::fromLocalFile(_fullpath);

        qDebug() << "_fullpath:" << _fullpath;
        qDebug() << "encodename:" << _encoded;
        qDebug() << "url:" << _url;

        if (QFile::exists(_fullpath)) {
            foo.saveString(cnt, _fullpath);
        } else {
            qDebug() << "_fullpath nok:" << _fullpath;
        }

        if (QFile::exists(_encoded)) {
            foo.saveEncoded(cnt, _encoded);
        } else {
            qDebug() << "check encode fail:" << _encoded;
        }

        foo.saveUrl(cnt, _url);

        cnt ++;
    }

    if (cnt == 0) {
        qWarning() << "no files found...";
    }
}

QUrl readUrl(int idx)
{
    qDebug() << Q_FUNC_INFO;
    Foo bar;
    QUrl url;
    if ( bar.readUrl(idx, url) ) {
        qDebug() << url;
        return url;
    }
    return QUrl();
}

void testread()
{
    qDebug() << Q_FUNC_INFO;
    Foo bar;
    QUrl url;
    int urlcount = bar.getUrlCount();

    for (int i=0; i<urlcount; i++) {
        if ( bar.readUrl(i, url) ) {
            qDebug() << url;
            bool ret = QFile::exists(url.toLocalFile());
            qDebug() << "exist?" /* << _f.fileName() << endl */
                 << ret;
        }
    }
}

void test_arg_format()
{
    double pi=3.1415926535897932;
    qDebug() << QString("<%1>").arg(pi, 0, 'f', 4);
}

QString getHomepath()
{
    QString home = QDir::homePath();
    QDir qq(home);
    qDebug() << "dirName" << qq.dirName();
    return home;
}

QString toPercentEncoding(const QString& str)
{
    return QUrl::toPercentEncoding(str, ",");
}

QString doSanity(const QString& str)
{
    QString res = str;
    res.replace("'", "''");
    return res;
}

void test_info()
{
    DeviceScreen ds;
    qDebug() << ds.getInfostring();
}

void test__pe()
{
    QString s = "03-Yes, My Dream";
    QString p = toPercentEncoding(s);
    qDebug() << p;
    QString result = QString("title=%1/message=%2").arg(p).arg("#####");
    qDebug() << result;
}

int main(int argc, char *argv[])
{
    //Q_UNUSED(argc);
    //Q_UNUSED(argv);

    for (int i=1; i<argc; ++i) {
        qDebug() << toPercentEncoding(argv[i]);
    }

    //qDebug() << getHomepath();
    //testdir( getHomepath() );
    //testread();
    //test_timezone();
    //test_locale();

    //test_read_ini();
    //QString s = "I don't know!";
    //qDebug() << "test:" << doSanity(s);

    //gtz();

    //test_info();

    test__pe();

    test_runscript();

    return 0;
}
