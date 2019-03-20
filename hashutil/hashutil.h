#ifndef __UTIL_HASHUTIL_H__
#define __UTIL_HASHUTIL_H__

// #if QT_VERSION < 0x050900
// #error need newer qt version
// #endif

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QMap>
#include <QCryptographicHash>
#include <QDebug>

typedef QString (*hash_func_ptr)(const char*, size_t);

class HashUtil
{
public:
    HashUtil() {
        init();
    }

    QString md5sum(const char* buffer, size_t size);
    void goThrough(const char* buffer, size_t size);

    void test();

protected:
    void init();

    QString generic_hasher(QCryptographicHash::Algorithm algo,
        const char* buffer, size_t size, QByteArray& arr);
    QString getHash(const QString& algo_name, const char* buffer, size_t size);

private:
    QMap<QString, QCryptographicHash::Algorithm> hasher;
};



#endif  // __UTIL_HASHUTIL_H__
