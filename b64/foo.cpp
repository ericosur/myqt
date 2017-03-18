#include "foo.h"

Foo::Foo()
{
    ini = new QSettings(DEFAULT_INI_PATH, QSettings::IniFormat);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    ini->setIniCodec(codec);
    qDebug() << "fn:" << ini->fileName();
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
