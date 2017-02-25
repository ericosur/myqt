#include <QCoreApplication>

#include "core.h"
#include "miscutil.h"


int main(int argc, char** argv)
{
    qInstallMessageHandler(msgHandler);
    QCoreApplication app(argc, argv);

    handleOpt(argc, argv);
    QObject::connect(Core::getInstance(), SIGNAL(sigQuitapp()), &app, SLOT(quit()));

    Core::getInstance()->start();

    return app.exec();
}
