/**
 * main.cpp
 */

#include "core.h"

#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include <unistd.h>

#include "commonutil.h"

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QCoreApplication app(argc, argv);

    Core::getInstance()->start();

    return app.exec();
}
