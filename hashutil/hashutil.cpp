#include "hashutil.h"

void HashUtil::init()
{
    // use all lower case at string part
    //QMap<QString, QCryptographicHash::Algorithm> hh =
    hasher =
    {
        {"md4", QCryptographicHash::Md4},
        {"md5", QCryptographicHash::Md5},
        {"sha1", QCryptographicHash::Sha1},
        {"sha224", QCryptographicHash::Sha224},
        {"sha256", QCryptographicHash::Sha256},
        {"sha384", QCryptographicHash::Sha384},
        {"sha512", QCryptographicHash::Sha512},
        {"sha3_224", QCryptographicHash::Sha3_224},
        {"sha3_256", QCryptographicHash::Sha3_256},
        {"sha3_384", QCryptographicHash::Sha3_384},
        {"sha3_512", QCryptographicHash::Sha3_512},
        {"keccak_224", QCryptographicHash::Keccak_224},
        {"keccak_256", QCryptographicHash::Keccak_256},
        {"keccak_384", QCryptographicHash::Keccak_384},
        {"keccak_512", QCryptographicHash::Keccak_512}
    };

    //hasher = hh;
}

QString HashUtil::generic_hasher(QCryptographicHash::Algorithm algo, const char* buffer, size_t size, QByteArray& arr)
{
    QCryptographicHash hash(algo);
    hash.addData(buffer, static_cast<int>(size));
    // result returns QByteArray
    arr = hash.result();
    return arr.toHex().data();
}

QString HashUtil::getHash(const QString& algo_name, const char* buffer, size_t size)
{
    if (!hasher.contains(algo_name)) {
        qWarning() << "[ERROR] no such algorithm name:" << algo_name;
        return QString();
    }
    QByteArray arr;
    QString ret = generic_hasher(hasher.value(algo_name), buffer, size, arr);
    qDebug() << "[INFO] result:" << ret;
    return ret;
}

QString HashUtil::md5sum(const char* buffer, size_t size)
{
    QByteArray arr;
    return generic_hasher(hasher.value("md5"), buffer, size, arr);
}

void HashUtil::goThrough(const char* buffer, size_t size)
{
    qDebug() << "input:" << buffer;
    QMap<QString, QCryptographicHash::Algorithm>::const_iterator it;
    for (it = hasher.cbegin(); it != hasher.cend(); ++it) {
        //qDebug() << *it;
        //qDebug() << it.key() << "=>" << it.value();
        QByteArray arr;
        QString ret = generic_hasher(it.value(), buffer, size, arr);
        int len = arr.count() * 8;
        QString msg = QString("%1 len(%2) = %3").arg(it.key()).arg(len).arg(ret);
        qDebug() << msg;
    }
}

void HashUtil::test()
{
    // data from: https://en.wikipedia.org/wiki/SHA-3
    Q_ASSERT(getHash("sha3_224", "", 0) == "6b4e03423667dbb73b6e15454f0eb1abd4597f9a1b078e3f5b5a6bc7");
    Q_ASSERT(getHash("sha3_256", "", 0) == "a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a");
    Q_ASSERT(getHash("sha3_384", "", 0) == "0c63a75b845e4f7d01107d852e4c2485c51a50aaaa94fc61995e71bbee983a2ac3713831264adb47fb6bd1e058d5f004");

    // https://emn178.github.io/online-tools/keccak_224.html
    Q_ASSERT(getHash("keccak_224", "", 0) == "f71837502ba8e10837bdd8d365adb85591895602fc552b48b7390abd");
    Q_ASSERT(getHash("keccak_256", "", 0) == "c5d2460186f7233c927e7db2dcc703c0e500b653ca82273b7bfad8045d85a470");
    Q_ASSERT(getHash("keccak_384", "", 0) == "2c23146a63a29acf99e73b88f8c24eaa7dc60aa771780ccc006afbfa8fe2479b2dd2b21362337441ac12b515911957ff");

}
