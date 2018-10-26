/// file: barcontrol.cpp

#include "barcontrol.h"
#include "foothread.h"
#include <QDebug>

#define FORK_MORE_THREAD    4
#define TEST_COUNT          50

BarControl::BarControl()
    : m_count(0)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    m_timer->start(750);

}

void BarControl::onStart()
{
    qDebug() << "onStart()";
}

void BarControl::onFinish()
{
    qDebug() << "onFinish";
}

void BarControl::onTimeout()
{
    qDebug() << "onTimeout:" << m_count;
    //qDebug() << "idealThreadCount():" << QThread::idealThreadCount();
    m_count++;

    // here will fork more threads, could watch how many threads within this process
    for (int i = 0; i < FORK_MORE_THREAD; i ++) {
        FooThread* flood = new FooThread();
        flood->start();
    }

    if (m_count > TEST_COUNT) {
        qDebug() << "emit sigClose";
        m_timer->stop();
        emit sigClose();
        emit sigAppQuit();
    }
}
