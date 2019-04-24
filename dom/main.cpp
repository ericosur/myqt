/// \file main.cpp
///

#include "domutil.h"

#include <QCoreApplication>
#include <QDebug>

void test()
{
    HandleSvg* svg = HandleSvg::getInstance();
    svg->test();
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();

    return 0;
}
