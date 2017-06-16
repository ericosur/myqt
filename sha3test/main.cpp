#include <QCoreApplication>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include "core.h"

int main(int argc, char** argv)
{
    // Q_UNUSED(argc);
    // Q_UNUSED(argv);
    QCoreApplication app(argc, argv);

    Core::getInstance()->start();

    return app.exec();
}
