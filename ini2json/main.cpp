#include <QCoreApplication>

#include "core.h"

int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    Core::getInstance()->start();
    return 0;
}