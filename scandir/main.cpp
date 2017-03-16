#include <QCoreApplication>
#include <QDebug>

#include "core.h"
#include "miscutil.h"


int main(int argc, char** argv)
{
    //qDebug()
    qInstallMessageHandler(msgHandler);
    //QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QCoreApplication app(argc, argv);

    if ( handleOpt(argc, argv) ) {
        QObject::connect(Core::getInstance(), SIGNAL(sigQuitapp()), &app, SLOT(quit()));
        Core::getInstance()->start();
        return app.exec();
    } else {
        qWarning() << "cannot be configured correctly, exit...";
        return 0;
    }

}
