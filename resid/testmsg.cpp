#include "testmsg.h"

#define STRING_NULL    ""

QString findFileLocation(const QString& fn)
{
    QStringList findlist;
    findlist << QDir::currentPath()
             << QDir::homePath()
             << QDir::tempPath();

    foreach (QString ph, findlist) {
        QString fullpath = QString("%1%2%3").arg(ph)
                                .arg(QDir::separator())
                                .arg(fn);
        if (QFile::exists(fullpath)) {
            return fullpath;
        }
    }

    return "";
}

QString getmsg(const QString& locale_name, int id)
{
    QString fn = findFileLocation(STRMSGINI);
    if (fn == "") {
        qWarning() << "string token file not found...";
        return STRING_NULL;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings ini(STRMSGINI, QSettings::IniFormat);
    ini.setIniCodec(codec);

    //qDebug() << "id:" << id;
    QString key = QString("/%1/%2").arg(locale_name).arg(id);
    return ini.value(key, STRING_NULL).toString();
}
