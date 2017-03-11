#include <QtCore>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <QSettings>
#include <QStringList>
#include <QByteArray>

#define INIFILE "test.ini"

void testini(const QString& key, const QString& val)
{
    QSettings ini(INIFILE, QSettings::IniFormat);
    ini.setValue(key, val);
    ini.sync();
}

void readini()
{
    QSettings ini(INIFILE, QSettings::IniFormat);
    QStringList sl = ini.allKeys();
    foreach (QString kk, sl) {
        QString value = ini.value(kk, "").toString();
        qDebug() << QString("[%1] - [%2]").arg(kk).arg(value);
	}
}

void test()
{
    QDir dir("./");
    QStringList filter;
    QFile _file;

    filter << "*.*";
    int cnt = 0;

    foreach (QString file, dir.entryList(filter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullpath = _info.filePath();
        qDebug() << QFile::encodeName(_fullpath);

        _file.setFileName(_fullpath);
        if (_file.exists(_fullpath)) {
            qDebug() << "ok";
            testini(QString::number(cnt), _fullpath);
            cnt ++;
        } else {
            qDebug() << "not ok:" << _fullpath;
        }
    }
}

void test2()
{
    QTextCodec *locale = QTextCodec::codecForLocale();
    qDebug() << "locale:" << locale->name();
}

QString showByteArray(const QByteArray& ba)
{
    QString resHex;
//    QString resDec;
    for (int i = 0; i < ba.size(); i++) {
        resHex.append( QString::number(ba.at(i), 16).rightJustified(2, '0') );
    }
//    resDec.append( QString::number(ba.at(i) );
    return resHex;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();
    test2();

    readini();
    QString s = "張學友";
    qDebug() << showByteArray(s.toUtf8());
    qDebug() << showByteArray(s.toLatin1());

    return 0;
}

