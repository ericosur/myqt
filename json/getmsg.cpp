#include <QString>
#include <QDir>
#include <QRegExp>
#include <QDebug>

#include "readjson.h"

#define STRMSGJSON   "strdef.json"

QString findFileLocation(const QString& fn)
{
    QStringList findlist;

#ifdef USE_YOSETARGET
    findlist << "/usr/share"
        << "/data/apps"
        << "/data"
        << "/misc"
        << "/tmp";
#endif

    findlist << QDir::currentPath()
             << QDir::homePath()
             << QDir::tempPath()
             << "./"
             << "../";


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


QString getmsg(const QString& locale_name, const QString& strid)
{
    qDebug() << __func__ << "locale:" << locale_name << ", strid:" << strid;
    QString fn = findFileLocation(STRMSGJSON);
    if (fn == "") {
        qWarning() << "string token file not found...";
        return "";
    } else {
        qDebug() << "file from:" << fn;
    }

    ReadJson rj(fn);
    if (!rj.loadFile()) {
        qWarning() << "readjson failed";
        return "";
    }

    //QJsonObject json = rj.getJobject();

    // if caller use integer id like 10001
    QRegExp re("\\d+");
    QString numid;
    QString node;
    QString result;
    if (re.exactMatch(strid)) {
        numid = strid;
    } else {
        node = QString("General.%1").arg(strid);
        //numid = json["General"].toObject()[strid].toString();
        numid = rj.getLeafString(node);
    }
    //qDebug() << "numid:" << numid;
    //result = json[locale_name].toObject()[numid].toString();
    node = QString("%1.%2").arg(locale_name).arg(numid);
    result = rj.getLeafString(node);
    return result;
}
