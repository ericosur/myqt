#include "readthread.h"

ReadThread::ReadThread()
{
    qDebug() << Q_FUNC_INFO << "created...";
    flag = true;
}

void ReadThread::run()
{
    qDebug() << Q_FUNC_INFO << "run start...";

    const int REPEAT_TIMES = 2500000;
    qint64 current = QDateTime::currentMSecsSinceEpoch();

    for (int i = 0 ; i < REPEAT_TIMES ; ++i) {
        test(i);
        if (!flag)
            break;
    }
    qDebug() << QDateTime::currentMSecsSinceEpoch() - current;

    //QThread::msleep(WAIT_MSEC_LENGTH);

    qDebug() << Q_FUNC_INFO << "run finished...";
}

QString ReadThread::test(int i)
{
    QString str = QString("repeat no %1").arg(i);
    QString md5 = md5sum(str.toUtf8().data(), str.toUtf8().size());
    QString sha3 = sha3_256sum(str.toUtf8().data(), str.toUtf8().size());

    return md5 + sha3;
    // if (i%100000==0) {
    //     qDebug() //<< "md5:" << md5.size() << endl
    //         << md5 << endl
    //         //<< "sha3:" << sha3.size() << endl
    //         << sha3;
    // }
}

void ReadThread::setFlag(bool b)
{
    mutex.lock();
    flag = b;
    mutex.unlock();
}

bool ReadThread::getFlag()
{
    mutex.lock();
    bool ret = flag;
    mutex.unlock();
    return ret;
}