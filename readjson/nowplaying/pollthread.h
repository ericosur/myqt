#ifndef __POLL_THREAD_H__
#define __POLL_THREAD_H__

#include <QObject>
#include <QThread>

class PollThread : public QThread
{
    Q_OBJECT

public:
    PollThread();
    void run();
    void requestStop() {
        mShouldStop = true;
    }
    void init();

signals:
    void sigPollTimeout();
    void sigRhsChanged();
    void sigLhsChanged();

private:
    bool mShouldStop = false;
    int cnt = 0;
};

#endif // __POLL_THREAD_H__
