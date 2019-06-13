#ifndef __CORE_H__
#define __CORE_H__

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>

#include "readthread.h"
#include <readjson.h>

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* _instance;
    static Core* getInstance();

    void start();

signals:
    void sigQuit();

public slots:
    void sltWaitFinished();
    void sltTimeout();
    // void sltUsbDetected();
    // void sltIpodDetected();

protected:
    Core();

private:
    ReadThread* thread = nullptr;
    ReadJson rj;
    QJsonObject json;
};

#endif  // __CORE_H__
