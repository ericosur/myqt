/**
 * \file main.cpp
 * \brief entry point and test function
 */


#include <QCoreApplication>
#include <QString>
#include <QTime>
#include <QDebug>
#include <iostream>

#include "jsetest.h"

#define USE_CORE_APPLICATION


/** customized message handler for rediecting qDebug() messages
 */
void msgHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
{
    using namespace std;

    Q_UNUSED(ctx);
    QString prefix = "[" + QTime::currentTime().toString("HH:mm:ss.zzz") + "] ";
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = prefix + QString("[%1] %2").arg( symbols[type] ).arg( msg );
    std::cerr << output.toStdString() << std::endl;
    if( type == QtFatalMsg ) abort();
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    qInstallMessageHandler(msgHandler);

#ifdef USE_CORE_APPLICATION
    QCoreApplication app(argc, argv);
#endif

    JSETest* se = JSETest::getInstance();

    qDebug() << "jse test...";
    se->test();

#ifdef USE_CORE_APPLICATION
    return app.exec();
#else
    return 0;
#endif
}
