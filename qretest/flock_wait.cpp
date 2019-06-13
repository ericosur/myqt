#include "testcases.h"
#include "flock_wait.h"
#include "flock.h"
#include "flock_broker.h"
#include <QDebug>

FlockWaitThread::FlockWaitThread()
{
    qDebug() << Q_FUNC_INFO << "created...";
}
void FlockWaitThread::run()
{
    FILE* fptr = nullptr;

    // block here if file lock is not granted
    fptr = util_file_lock_wait(PIDFILE);
    qDebug() << "file lock is released by another process...";

    if (fptr != nullptr) {
        FlockBroker::getInstance()->setLockPtr(fptr);
    }
}
