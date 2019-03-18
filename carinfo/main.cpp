//#include <QCoreApplication>
//#include <QProcess>
#include <QDebug>
#include <stdio.h>

#include "carvalue.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    CarValue* vars = CarValue::getInstance();
    vars->load();
    vars->dump();

    return 0;
}
