#include "util.h"
#include "trypath.h"

QString getHomepath()
{
    QString home = QDir::homePath();
    QDir qq(home);
    if (gDebug)
        qDebug() << "homePath:" << qq.dirName();
    return home;
}


///
/// _list contains list for search paths
/// _file is filename to be searched
/// result is first existed fullpath for _file
///
bool searchFileFromList(const QStringList& _list, const QString& _file, QString& result)
{

    foreach (QString pp, _list) {
        //qDebug() << pp;
        QDir dir( pp );
        QString dirpath;
        if (dir.exists()) {
            dirpath = QString("%1/%2").arg(dir.canonicalPath()).arg(_file);
            if (gDebug)
                qDebug() << dirpath;
            if (QFile::exists(dirpath)) {
                result = dirpath;
                return true;
            }
        }
    }
    result = "";
    return false;
}
