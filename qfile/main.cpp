#include <QtCore>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <QSettings>

QSettings ini("test.ini", QSettings::IniFormat);

void testini(const QString& key, const QString& val)
{
    ini.setValue(key, val);
    ini.sync(); 
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


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();
    test2();

    return 0;
}

