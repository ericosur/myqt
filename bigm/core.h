#ifndef __CORE_H__
#define __CORE_H__

#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

#define MY_BIG_MEMORY_SIZE      (512*1024)
#define MY_TIMER_LENGTH         (5*1000)

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* getInstance();

    void helloWorld();


signals:
    void sigQuit();

public slots:
    void sltTimeout();


protected:
    static Core* _instance;
    explicit Core();

private:
    QTimer* mTimer = nullptr;
    quint8* mymem = nullptr;
    bool bFinish = false;
};


#endif  // __CORE_H__
