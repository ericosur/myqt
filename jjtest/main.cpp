/// \file main.cpp
///

#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "foo.h"
#include "bar.h"


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test_foo();
    test_bar();

    return 0;
}
