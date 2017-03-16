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

#define DEFAULT_CONFIG_PATH "scandir.ini"

using namespace std;
bool bDebug = true;

void msgHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
{
    Q_UNUSED(ctx);
    QString prefix = QString("[%1][%2]")
        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
        .arg(qApp->applicationName());
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = prefix + QString("[%1] %2").arg( symbols[type] ).arg(msg);

    if ( type == QtDebugMsg || type == QtInfoMsg ) {
        if (bDebug)  {
            std::cout << output.toStdString() << std::endl;
        }
    } else {
        std::cout << output.toStdString() << std::endl;
    }
    if ( type == QtFatalMsg )
        abort();
}

void print_help()
{
    printf("help!\n"
        "default config from: %s\n\n"
        "-c config file name\n"
        "-i input dir\n"
        "-o output dir\n"
        "-h help message\n",
        DEFAULT_CONFIG_PATH
        );
}

bool handleOpt(int argc, char** argv)
{
    bool configured = false;
    do {
        if (argc == 1) {
            print_help();

            qDebug() << "use default config:" << DEFAULT_CONFIG_PATH;
            configured = Core::getInstance()->setConfigFilename(DEFAULT_CONFIG_PATH);
            break;
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
                configured = Core::getInstance()->setConfigFilename(optarg);
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
    } while (false);

    qDebug() << Q_FUNC_INFO << "end...";
    return configured;
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

#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE           64
#define MAX_MSG_SIZE            MAX_SEND_SIZE
#define SAFETY_CLEARANCE   2
struct mymsgbuf {
    long mtype;
    char mtext[MAX_SEND_SIZE];
};


int send_msgq(int key, int type, const char* str)
{
    int msqid;
    struct mymsgbuf buf;
    int sendlength;

    printf("send_msgq(): key: 0x%08X\ntype: %d\nstr: %s\n", key, type, str);
    msqid = msgget( key, 0660 | IPC_CREAT );
    /* msqid = msgget( key, 0660 | IPC_EXCL ); */
    if ( msqid < 0 ) {
        perror("msgsnd: create message queue error");
        return -1;
    } else {
        printf("msgsnd: msqid: %d\n", msqid);
    }

    buf.mtype = type;
    sendlength = sizeof(struct mymsgbuf) - sizeof(long);
    memset(buf.mtext, 0, MAX_SEND_SIZE);
    strncpy(buf.mtext, str, MAX_SEND_SIZE - SAFETY_CLEARANCE);

    if ( msgsnd(msqid, &buf, sendlength, 0) < 0 ) {
        perror("msgsnd: send message error");
        return -1;
    }
    //printf("sendMyMessage: %s\n", buf.mtext);
    return 0;
}
