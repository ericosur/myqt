/// \file main.cpp
///

#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "testload.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test_load();

    return 0;
}
