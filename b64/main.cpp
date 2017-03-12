#include <QCoreApplication>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QSettings>

QString dump(const char* buf, int size)
{
    QString res;
    for (int i = 0; i<size; i++) {
        printf("%02x ", (int)buf[i]);
    }
    return res;
}

void saveIni(const QString& key, const QByteArray& value)
{
    QSettings ini("test.ini", QSettings::IniFormat);
    ini.setValue(key, value);
    ini.sync();
}

void readIni(const QString& key, QByteArray& value)
{
    QSettings ini("test.ini", QSettings::IniFormat);
    if (!ini.contains(key)) {
        qWarning() << "key not found:" << key;
        return;
    }
    value = ini.value(key, QByteArray()).toByteArray();
}


void test(const QString& str)
{
    qDebug() << Q_FUNC_INFO << "str:" << str;

    QByteArray b1 = str.toLocal8Bit();
    qDebug() << "local 8bit" << b1.toHex() << endl
             << b1.toBase64();
    saveIni("key1", b1);
    QByteArray b2 = str.toUtf8();
    qDebug() << "utf8" << b2.toHex() << endl
             << b2.toBase64();
    saveIni("key2", b2);

    QByteArray bb;
    readIni("key1", bb);
    qDebug() << "bb" << bb.toHex();
    readIni("key2", bb);
    qDebug() << "bb" << bb.toHex();

    QString s = bb;
    qDebug() << "str==>" << s;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test("中文輸入法");
    test("\u5f37\u5f69\u4e0a\u4e0b");
    test("جميع أغاني");

    return 0;
}
