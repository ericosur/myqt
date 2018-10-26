#ifndef FOOTHREAD_H
#define FOOTHREAD_H

#include <QObject>
#include <QThread>

class FooThread : public QThread
{
    Q_OBJECT

public:
    FooThread();

    void run();

public slots:
    void onClose();


private:
    int fileno = -1;

};

#endif // FOOTHREAD_H
