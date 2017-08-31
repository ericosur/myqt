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
    mymem = new quint8[MY_BIG_MEMORY_SIZE];
    mTimer = new QTimer(this);
    mTimer->setSingleShot(false);

    connect(mTimer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
    connect(this, SIGNAL(sigQuit()), qApp, SLOT(quit()));
}


void Core::helloWorld()
{
    qDebug() << "Hello world!";
    mTimer->start(MY_TIMER_LENGTH);
}

void Core::sltTimeout()
{
    if (bFinish) {
        qDebug() << "will finish bigm...";
        emit sigQuit();
    } else {
        qDebug() << "will delete mymem...";
        delete mymem;
        bFinish = true;
    }
}
