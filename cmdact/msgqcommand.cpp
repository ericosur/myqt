#include "msgqcommand.h"

#include <QDebug>

MyCtrl::MyCtrl()
{
    initHash();
}

void MyCtrl::initHash()
{
    myhash["test"] = &MyCtrl::actTest;
    qDebug() << myhash["test"];
}

void MyCtrl::qmlRunCommand(const QString& cmd)
{
    doCommand(cmd);
}

void MyCtrl::doCommand(const QString& cmd)
{
    if (myhash.contains(cmd)) {
        fp = myhash[cmd];
        // a very strange way to call function pointer to current class
        (*this.*fp)();
    } else {
        qDebug() << Q_FUNC_INFO << "NO such command!!";
        emit sigError();
    }
}

void MyCtrl::actTest()
{
    qDebug() << Q_FUNC_INFO;
    emit sigTest();
}
