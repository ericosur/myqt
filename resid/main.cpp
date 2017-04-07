#include <QCoreApplication>
#include <QDebug>
//#include <iostream>

#include "testmsg.h"
#include "strdef.h"

//using namespace std;

void test_ar_id(int id)
{
    QString str = getmsg("ar_AE", id);
    qDebug() << str;
}

void test_zh_id(int id)
{
    QString str = getmsg("zh_CN", id);
    qDebug() << str;
}

void test()
{
    int id = MSG_PLEASE_CONNECT;
    test_ar_id(id);
    test_zh_id(id);
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();

    return 0;
}
