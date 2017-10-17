#include "core.h"

#define TIMEOUT_TO_STOP_THREAD     5000

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
    qDebug() << Q_FUNC_INFO << "created...";

    if (thread == NULL) {
        thread = new ReadThread();
    }
    // connect(poll, SIGNAL(sigUsbDectected()), this, SLOT(sltUsbDetected()));
    // connect(poll, SIGNAL(sigIpodDectected()), this, SLOT(sltIpodDetected()));
    connect(thread, SIGNAL(finished()), this, SLOT(sltWaitFinished()));
    connect(this, SIGNAL(sigQuit()), qApp, SLOT(quit()));
}

void Core::start()
{
    qDebug() << Q_FUNC_INFO;
    if (thread == NULL) {
        qWarning() << "thread is NULL, exit...";
        return;
    }
    qDebug() << "TIMEOUT_TO_STOP_THREAD:" << TIMEOUT_TO_STOP_THREAD;
    QTimer::singleShot(TIMEOUT_TO_STOP_THREAD, this, SLOT(sltTimeout()));
    thread->start();

}

void Core::sltWaitFinished()
{
    qDebug() << Q_FUNC_INFO << "thread finished";
    emit sigQuit();
}

void Core::sltTimeout()
{
    qDebug() << "timeout...";
    thread->setFlag(false);
}
