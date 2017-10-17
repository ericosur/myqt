#include "commonutil.h"


// using stdc FILE* to write
bool writeStringToFile(const QString& str, const QString& fn)
{
    FILE* fp = fopen(fn.toUtf8().constData(), "w");
    if (fp == NULL) {
        qDebug() << "cannot write file:" << fn;
        return false;
    }
    fprintf(fp, "%s", str.toUtf8().constData());
    fclose(fp);
    //qDebug() << "writeStringToFile(): write to" << fn;
    return true;
}

// using QFile to write
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn)
{
    QFile outFile(fn);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "fail to write file:" << fn;
        return false;
    }
    if ( outFile.write(arr) == -1 ) {
        return false;
    }
    return true;
}
