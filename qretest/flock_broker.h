#ifndef __FLOCK_BROKER_H__
#define __FLOCK_BROKER_H__

#include <QObject>
#include <QDebug>
#include <stdio.h>
#include "flock_wait.h"
#include "funlock_wait.h"

class FlockBroker : public QObject
{
    Q_OBJECT

public:
    static FlockBroker* getInstance();

    void startLockWait();
    void startUnlockWait();
    void setLockPtr(FILE* ptr);
    FILE* getLockPtr();
    FlockWaitThread* getWaitLock();
    FunlockWaitThread* getWaitUnlock();

public slots:
    void sltLockWaitFinished();
    void sltUnlockWaitFinished();

protected:
    static FlockBroker* _instance;
    FlockBroker();

private:
    FILE* lock_ptr = NULL;
    FlockWaitThread* waitlock = NULL;
    FunlockWaitThread* waitunlock = NULL;
};


#endif  // __FLOCK_BROKER_H__
