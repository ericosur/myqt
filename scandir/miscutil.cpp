#include <QTime>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "miscutil.h"
#include "core.h"

using namespace std;
void msgHandler(QtMsgType type, const QMessageLogContext& ctx, const QString&
msg)
{
    Q_UNUSED(ctx);
    QString prefix = QString("[%1][%2]")
        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
        .arg(qApp->applicationName());

    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = prefix + QString("[%1] %2").arg( symbols[type] ).arg( msg
 );
    std::cerr << output.toStdString() << std::endl;
    if ( type == QtFatalMsg )
        abort();
}

void print_help()
{
    printf("help!\n"
        "-c config file name\n"
        "-i input dir\n"
        "-o output dir\n"
        "-h help message\n"
        );
}

void handleOpt(int argc, char** argv)
{
    if (argc == 1) {
        print_help();
        exit(-1);
    }

    while(1) {
        int cmd_opt = getopt(argc, argv, "c:hi:o:");
        if (cmd_opt == -1) {
            //qDebug() << "cmd_opt == -1";
            break;
        }
        switch (cmd_opt) {
        case 'h':   // help
            print_help();
            exit(2);
            break;
        case 'c':   // config
            qDebug() << "c:" << optarg;
            Core::getInstance()->setConfigFilename(optarg);
            break;
        case 'i':   // input dir
            qDebug() << "i:" << optarg;
            Core::getInstance()->setInputdir(optarg);
            break;
        case 'o':   // output dir
            Core::getInstance()->setOutputdir(optarg);
            break;
        default:
            exit(0);
            break;
        }
    }
    qDebug() << Q_FUNC_INFO << "end...";
}

QString md5sum(const char* buffer, int size)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(buffer, size);
    QString str_hash = hash.result().toHex().data();
    return str_hash;
}

bool isFileExisted(const QString& fn)
{
    QFile fileobj(fn);
    return fileobj.exists();
}
