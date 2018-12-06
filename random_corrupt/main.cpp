/// \file main.cpp
///

#include <QCoreApplication>
#include <QDebug>

#include "util.h"
#include "core.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    Core* pcore = Core::getInstance();

    handleOpt(argc, argv);
    qDebug() << "debug mode:" << pcore->bDebug;

    pcore->action();


    return 0;
}
