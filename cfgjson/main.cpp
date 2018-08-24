//#include <QCoreApplication>
//#include <QProcess>
#include <QDebug>
//#include <stdio.h>

#include "getradioconfig.h"


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);


    GetRadioConfig* cfg = GetRadioConfig::getInstance();

    // cfg->browse_dir();
    // cfg->test();

    cfg->test_from_scratch();

    return 0;
}
