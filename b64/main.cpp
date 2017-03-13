#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "foo.h"

void testdir()
{
    Foo foo;

#ifdef __arm__
    QDir dir("/data/rasmus");
#else
    QDir dir("/home/rasmus/src/myqt/b64/b");
#endif
    QStringList filter;
    QFile _file;

    filter << "*.mp3" << "*.m4a" << "*.ape";
    int cnt = 0;

    foreach (QString file, dir.entryList(filter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullpath = _info.filePath();
        QString _encoded = QFile::encodeName(_fullpath);
        QUrl _url = QUrl::fromLocalFile(_fullpath);
        //_url.fromEncoded(_encoded.toUtf8());

        qDebug() << "_fullpath:" << _fullpath;
        qDebug() << "encodename:" << _encoded;
        qDebug() << "url:" << _url;

        _file.setFileName(_fullpath);
        if (_file.exists(_fullpath)) {
            foo.saveString(cnt, _fullpath);
        } else {
            qDebug() << "_fullpath nok:" << _fullpath;
        }

        _file.setFileName(_encoded);
        if (_file.exists(_encoded)) {
            foo.saveEncoded(cnt, _encoded);
        } else {
            qDebug() << "check encode fail:" << _encoded;
        }

        foo.saveUrl(cnt, _url);

        cnt ++;
    }
}

QUrl readUrl(int idx)
{
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
    Foo bar;
    QUrl url;
    QFile _f;
    int urlcount = bar.getUrlCount();

    for (int i=0; i<urlcount; i++) {
        if ( bar.readUrl(i, url) ) {
            qDebug() << url;
            _f.setFileName(url.toLocalFile());
            qDebug() << "exist?" /* << _f.fileName() << endl */
                 << _f.exists();
        }
    }
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    testdir();
    testread();

    return 0;
}
