#include "pollthread.h"

#include <QDebug>

#define SLEEP_DURING_POLLING    (2000)


PollThread::PollThread()
{
    qDebug() << Q_FUNC_INFO << "created";
    init();
}

void PollThread::init()
{
    mShouldStop = false;
}

void PollThread::run()
{
    qDebug() << "pollthread start running...";
    while ( true ) {
        QThread::msleep(SLEEP_DURING_POLLING);
        qDebug() << "emit sigPollTimeout()";
        emit sigPollTimeout();

        cnt ++;
        if (cnt % 2 == 0) {
            emit sigRhsChanged();
        } else {
            emit sigLhsChanged();
        }


        if ( mShouldStop ) {
            qDebug() << "request to stop polling...";
            break;
        }
    }

    // reset mShouldStop flag after thread finished
    mShouldStop = false;
    qDebug() << "pollthread finished...";
}
