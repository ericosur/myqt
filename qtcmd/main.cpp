#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QDateTime>
#include <QByteArray>
#include <iostream>
#include <fstream>
#include <string.h>

#include "testutil.h"

#include "wait.h"
#include "retry.h"

#include "commonutil.h"
#include "jsonutil.h"

using namespace std;

QString getLinkRealname(const QString& softlink);

void test_qprocess()
{
//#define TEST_COMMAND    "du -chs /home/rasmus/gcode/snippet/"
#define TEST_COMMAND    "ls no.such.file.existed.32424"

    QProcess process;
    process.start(TEST_COMMAND);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    qDebug() << "stdout:" << stdout;
    qDebug() << "stderr:" << stderr;
    qDebug() << "return code:" << process.exitCode();
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

void test_fromconfig()
{
    try {
        std::ifstream infile(gVars.sConfig.toUtf8().data());
        nlohmann::json j;
        infile >> j;

        qDebug() << "parsed!";

        // iterate the array
        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            //std::cout << it.key() << ":" << it.value() << std::endl;
            for (auto& e: j[it.key()]) {
                std::string key = it.key();
                getHash(key.c_str(), e.get<std::string>().c_str());
            }
        }

    } catch (nlohmann::json::parse_error& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
    }

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
        case TC_READCONFIG:
            test_fromconfig();
            return 0;
        case TC_PROCESS:
            test_qprocess();
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
