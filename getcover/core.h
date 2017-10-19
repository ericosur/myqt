#ifndef __CORE_H__
#define __CORE_H__

#include <QObject>
#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include "worker.h"

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* _instance;
    static Core* getInstance();

    void start();

signals:
    void sigQuit();
    void sigStart();

public slots:
    void sltWaitFinished();

protected:
    Core();

private:
    Worker* worker = NULL;
};

#endif  // __CORE_H__
