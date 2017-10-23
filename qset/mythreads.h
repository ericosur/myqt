#ifndef MYTHREADS_H
#define MYTHREADS_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
#include <QString>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>

#define MAX_HASH_REPEAT_METHOD_1    40
#define MAX_HASH_REPEAT_METHOD_2    40
#define MAX_HASH_REPEAT_METHOD_3    40
#define MAX_TEST_REPEAT             20


class MyEmptyThread : public QThread
{
    Q_OBJECT

public:
    enum THREAD_METHOD {
        TH_NULL,
        TH_METHOD1,
        TH_METHOD2,
        TH_METHOD3
    };

public:
    MyEmptyThread();
    ~MyEmptyThread() {}

    QString getResult() const {
        return mResult;
    }

    int getCount() const {
        return mCount;
    }

    quint64 getEpoch() const {
        return e.elapsed();
    }

protected:
    static QString doHardWork(const QString& s, THREAD_METHOD method=TH_METHOD1);
    static QByteArray doHash(int repeat_times, QCryptographicHash::Algorithm algo);

protected:
    QString mResult;
    int mCount = 0;
    QElapsedTimer e;
};


class ThreadFoo : public MyEmptyThread
{
    Q_OBJECT

public:
    ThreadFoo(const QString& name, THREAD_METHOD method, const QString& initstr);
    ~ThreadFoo() {}
    void run();
    QString getName() const {
        return mName;
    }

signals:
    void threadFinished(const QString& s);

public slots:
    void onFinished();

private:
    THREAD_METHOD mMethod = TH_METHOD1;
    QString mStr;
    QString mName;
};


#endif // MYTHREADS_H
