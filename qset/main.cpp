/// \file main.cpp
#include <QCoreApplication>

#include "core.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Core::getInstance()->start();

    return a.exec();
}
