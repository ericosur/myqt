#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QDateTime>
#include <QByteArray>
#include <iostream>
#include <string.h>

#include "testutil.h"

#include "wait.h"
#include "retry.h"
#include "pass.h"

using namespace std;

QString getLinkRealname(const QString& softlink);

void test()
{
    QProcess process;
    process.start("du -chs /home/rasmus/gcode/snippet/");
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    qDebug() << "stdout: " << stdout;
    qDebug() << "stderr: " << stderr;
}

void gen_seed()
{
    qint64 current = QDateTime::currentMSecsSinceEpoch();
    qsrand((uint)(current % 0xffffffff));
}


void test_array()
{
//#define DEFAULT_VIDEO_SOFTLINK  "/var/run/front.videomgr"
#define DEFAULT_VIDEO_SOFTLINK  "/home/rasmus/我的連結"
    getLinkRealname(DEFAULT_VIDEO_SOFTLINK);
}

QString get_one_string(int idx)
{
    QStringList sl;
    sl << "1234" << "apple" << "ball" << "cat" << "dog";

    return sl.at(idx % sl.size());
}

QString get_md5sum(const QString& str)
{
    char *input = str.toUtf8().data();
    QString md = md5sum(input, strlen(input));
    qDebug() << QString("%1 => %2").arg(str).arg(md);
    return md;
}

void test_md5list(int count)
{
    for (int i = 0; i < count; i++) {
        QString md = get_md5sum(get_one_string(i));
        //qDebug() << QString("%1 => %2").arg(str).arg(md);
        if ( md == CIPHER_HASH ) {
            qWarning() << "parameter matched !!";
        }
    }
}

void test_sha1hmac()
{
    QByteArray key = gVars.sKeystring.toUtf8();
    QByteArray str = gVars.sTeststring.toUtf8();
    qDebug() << QString("key:%1,str:%2 ==> %3").arg(gVars.sKeystring)
                    .arg(gVars.sTeststring)
                    .arg(hmacSha1(key, str));
}

QString get_sha1sum(const QString& str)
{
    char *input = str.toUtf8().data();
    QString md = sha1sum(input, strlen(input));
    qDebug() << QString("%1 => %2").arg(str).arg(md);
    return md;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    handleOpt(argc, argv);
    switch (gVars.kTest) {
        case TC_MD5LISTTEST:
            test_md5list(gVars.iCount);
            return 0;
        case TC_ARRAYTEST:
            test_array();
            return 0;
        case TC_MD5SUMTEST:
            get_md5sum(gVars.sTeststring);
            return 0;
        case TC_SHA1SUMTEST:
            get_sha1sum(gVars.sTeststring);
            return 0;
        case TC_HMACTEST:
            test_sha1hmac();
            return 0;
        default:
            test_md5list(1);
            return 0;
    }

    WaitOneSecond t1("t1", 2000), t2("t2", 4000);
    WaitOneSecond w("wait", 8000);
    RetryThread foobar;

    // after thread WaitOneSecond finised, it also quit this app
    QObject::connect(&t1, SIGNAL(finished()), &t2, SLOT(start()));
    QObject::connect(&t2, SIGNAL(finished()), &foobar, SLOT(sltNotifyStop()));
    QObject::connect(&w, SIGNAL(finished()), &foobar, SLOT(sltNotifyStop()));
    QObject::connect(&w, SIGNAL(finished()), &app, SLOT(quit()));

    w.start();
    t1.start();
    foobar.start();

    return app.exec();
}
