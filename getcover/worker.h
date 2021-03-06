/**
 * \file worker.h
 */

#ifndef __WORKER_H__
#define __WORKER_H__

#include <QThread>
#include <QCryptographicHash>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();

public slots:
    void sltStart();

signals:
    void sigFinish();

protected:
    void do_something();

private:
    QThread* mThread = nullptr;

};

#endif  // __WORKER_H__
