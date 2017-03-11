#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "pass.h"

int main(int argc, char** argv)
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
//    QCoreApplication app(argc, argv);
//    return app.exec();
    const char buf[] = "hello world";
    QString md5 = md5sum(buf, sizeof(buf)); 
    QString sha3 = sha3_256sum(buf, sizeof(buf));

    qDebug() << "md5:" << md5.size() << endl
        << md5 << endl
        << "sha3:" << sha3.size() << endl
        << sha3 << endl;

    return 0;
}

