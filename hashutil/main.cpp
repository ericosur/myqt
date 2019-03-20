/// \file main.cpp
///

#include <QCoreApplication>
#include <QDebug>

#include <string.h>

#include "hashutil.h"

void test()
{
    HashUtil hu;

    hu.test();

    const char str_test[] = "";
    qDebug() << hu.md5sum(str_test, strlen(str_test));

    hu.goThrough(str_test, strlen(str_test));

}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();

    return 0;
}
