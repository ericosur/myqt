#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "foo.h"

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

QString getHomepath()
{
    QString home = QDir::homePath();
    return home;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);


    testdir( getHomepath() );
    //testread();

    return 0;
}
