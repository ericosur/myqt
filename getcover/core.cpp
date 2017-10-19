#include "core.h"

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

    if (worker == NULL) {
        worker = new Worker();
    }

    connect(this, SIGNAL(sigQuit()), qApp, SLOT(quit()));
    connect(this, SIGNAL(sigStart()), worker, SLOT(sltStart()));
    connect(worker, SIGNAL(sigFinish()), qApp, SLOT(quit()));
}

void Core::sltWaitFinished()
{
    qDebug() << "worker thread is finished... and exit...";
    emit sigQuit();
}

void Core::start()
{
    emit sigStart();
}
