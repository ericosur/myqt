/// \file main.cpp
///

#include <QApplication>
#include <QString>
#include <QDebug>

#include "wordutil.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WordUtil* wu = WordUtil::getInstance();
    wu->test();

    return 0;
}
