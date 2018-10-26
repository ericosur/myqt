/// file: foothread.cpp

#include "foothread.h"
#include "filelock.h"

#include <unistd.h>
#include <QDebug>

#define MYLOCK_FILE     "/tmp/foo_thread.lck"

FooThread::FooThread()
{
}

void FooThread::run()
{
    if (FileLock::myflock(MYLOCK_FILE, fileno) == 0) {
        qDebug() << "file locked...";
    } else {
        qDebug() << "failed to lock... quit";
        return;
    }

    while (1) {
        usleep(1000*1000);
    }

    FileLock::myfunlock(fileno);
}

void FooThread::onClose()
{
    qDebug() << "FooThread::onClose()";
    this->terminate();
}
