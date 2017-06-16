#ifndef __READ_THREAD_H__
#define __READ_THREAD_H__

#include <QObject>
#include <QThread>
#include <QString>
#include <QDateTime>
#include <QMutex>
#include <QDebug>

#include "pass.h"

class ReadThread : public QThread
{
    Q_OBJECT

public:
    ReadThread();

    void run();
    QString test(int i);
    void setFlag(bool b);
    bool getFlag();

protected:

private:
    bool flag;
    QMutex mutex;
};

#endif // __READ_THREAD_H__
