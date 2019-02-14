#include "core.h"

#include <QDateTime>

#define TIMEOUT_TO_STOP_THREAD     9999
#define JSON_RESULT                "result.json"

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

    if (!rj.loadFile(JSON_RESULT)) {
        qWarning() << "[ERROR] failed to load:" << JSON_RESULT;
    }
    json = rj.getJobject();
    json["create"] = QDateTime::currentMSecsSinceEpoch();
}

void Core::start()
{
    qDebug() << Q_FUNC_INFO;

    json["start"] = QDateTime::currentMSecsSinceEpoch();

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
    json["finish"] = QDateTime::currentMSecsSinceEpoch();
    ReadJson::saveFile(JSON_RESULT, json);
    emit sigQuit();
}

void Core::sltTimeout()
{
    qDebug() << Q_FUNC_INFO << "timeout...";
    thread->setFlag(false);

    json["timeout"] = QDateTime::currentMSecsSinceEpoch();
    rj.setJobject(json);
    rj.saveFile(JSON_RESULT);
}
