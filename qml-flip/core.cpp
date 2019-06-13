#include "core.h"

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{

}

QQmlApplicationEngine* Core::getEngine()
{
    if (mEngine == nullptr) {
        mEngine = new QQmlApplicationEngine;
    }
    return mEngine;
}

void Core::hello()
{
    qDebug() << "hello world!";
}

