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

}

QQmlApplicationEngine* Core::getEngine()
{
    if (mEngine == NULL) {
        mEngine = new QQmlApplicationEngine;
    }
    return mEngine;
}

void Core::hello()
{
    qDebug() << "hello world!";
}

