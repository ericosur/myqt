#ifndef __FOO_H__
#define __FOO_H__

#include <QString>
#include <QByteArray>
#include <QUrl>
#include <QSettings>

#define DEFAULT_INI_PATH "/tmp/test.ini"

class Foo
{
public:
    Foo(const QString& inifn = DEFAULT_INI_PATH);
    ~Foo() {
        if (ini!=NULL) {
            ini->sync();
        }
    }

    QString getInifn() const {
        return mInifn;
    }

    void clear();

    void saveByteArray(const QString& key, const QByteArray& value);
    void saveString(int idx, const QString& str);
    void readByteArray(const QString& key, QByteArray& value);
    void saveUrl(int idx, const QUrl& url);
    void saveEncoded(int idx, const QString& enc);
    bool readUrl(int idx, QUrl& url);

    int getUrlCount();

private:
    QString mInifn;
    QSettings *ini = NULL;
};

void testdir(const QString& _home);
void testread();

#endif
