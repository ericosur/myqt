#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QtQml>
#include <QDebug>
#include <iostream>

#include "imagectrl.h"

void msgHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
{
    Q_UNUSED(ctx);
    QString prefix = QString("[%1][%2]")
        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
        .arg(qApp->applicationName());
    const char symbols[] = { 'I', 'E', '!', 'X' };
    QString output = prefix + QString("[%1] %2").arg( symbols[type] ).arg(msg);

    if ( type == QtDebugMsg || type == QtInfoMsg ) {
        std::cout << output.toStdString() << std::endl;
    } else {
        std::cout << output.toStdString() << std::endl;
    }
    if ( type == QtFatalMsg )
        abort();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(msgHandler);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("imagectrl", ImageCtrl::getInstance());
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}

