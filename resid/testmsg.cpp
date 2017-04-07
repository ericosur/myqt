#include "testmsg.h"

#define STRING_NULL    ""

QString getmsg(const QString& locale_name, int id)
{
    if (!QFile::exists(STRMSGINI)) {
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
