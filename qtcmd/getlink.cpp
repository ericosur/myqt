#include <QString>
#include <QByteArray>
#include <QDebug>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


QString getLinkRealname(const QString& softlink)
{
    qDebug() << Q_FUNC_INFO << softlink;
    struct stat sb;
    QByteArray arr;

    if ( lstat(softlink.toUtf8().constData(), &sb) == -1 ) {
        perror("lstat");
        return "";
    }

    arr.resize(sb.st_size);
    ssize_t r = readlink(softlink.toUtf8().constData(), arr.data(), sb.st_size);
    if (r < 0) {
        perror("lstat");
        return "";
    }
    if (r > sb.st_size) {
        arr.resize(r);
        qWarning() << "size of symlink increased";
    }

    qWarning() << "readlink:" << arr;
    return arr;
}
