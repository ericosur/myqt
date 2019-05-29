#include "util.h"
#include "foo.h"
#include "commontest.h"

#include <QTextCodec>
#include <QDebug>

Foo::Foo(const QString& inifn)
{
    mInifn = inifn;
    ini = new QSettings(mInifn, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    ini->setIniCodec(codec);
    CHECK_IF_DEBUG(qDebug() << "inifn:" << ini->fileName());
    ini->setValue("key", "test");
}

void Foo::clear()
{
    ini->clear();
}

void Foo::saveByteArray(const QString& key, const QByteArray& value)
{
    QString _key = QString("ba-%1").arg(key);
    ini->setValue(_key, value);
}

void Foo::saveString(int idx, const QString& str)
{
    QString key = QString("str%1").arg(idx);
    ini->setValue(key, str);
}

void Foo::saveEncoded(int idx, const QString& enc)
{
    QString key = QString("enc%1").arg(idx);
    ini->setValue(key, enc);
}

void Foo::saveUrl(int idx, const QUrl& url)
{
    QString key = QString("url%1").arg(idx);
    ini->setValue(key, url);
}

void Foo::readByteArray(const QString& key, QByteArray& value)
{
    if (!ini->contains(key)) {
        qWarning() << "key not found:" << key;
        return;
    }
    value = ini->value(key, QByteArray()).toByteArray();
}
bool Foo::readUrl(int idx, QUrl& url)
{
    QString key = QString("url%1").arg(idx);
    if (!ini->contains(key)) {
        qWarning() << "key not found:" << key;
        return false;
    }
    url = ini->value(key, "").toUrl();
    return true;
}

int Foo::getUrlCount()
{
    QStringList sl = ini->allKeys();
    QStringList result = sl.filter("url");
    return result.size();
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
    qDebug() << "will output search result to:" << foo.getInifn();
    filter << "*.mp3" << "*.m4a" << "*.ape" << "*.wav";
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

void testread()
{
    print_title(__func__);
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
