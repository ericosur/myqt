#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <iostream>

#include "nowplaycore.h"

bool g_messageVerbose = true;

/**
    \brief myMessageOutput() is customized message handler to redirect qDebug()
**/
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    using namespace std;
    QString txt;
    QString prefix = QString("[%1][%2][%3] ")
                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                        .arg(qApp->applicationName())
                        .arg(qApp->applicationPid());

    // special filter some messages
    // if (msg.contains("Unable to fetch row")) {
    //     return;
    // }

    switch (type) {
        case QtDebugMsg:
            txt = prefix + QString("D: %1").arg(msg);
            if (g_messageVerbose)
                cout << txt.toUtf8().data() << endl;
            break;
        case QtWarningMsg:
            txt = prefix + QString("W: %1").arg(msg);
            cout << txt.toUtf8().data() << endl;
            break;
        case QtCriticalMsg:
            txt = prefix + QString("C: %1").arg(msg);
            cout << txt.toUtf8().data() << endl;
            break;
        case QtInfoMsg:
            txt = prefix + QString("I: %1").arg(msg);
            if (g_messageVerbose)
                cout << txt.toUtf8().data() << endl;
            break;
        case QtFatalMsg:
            txt = prefix + QString("F: %1").arg(msg);
            cout << txt.toUtf8().data() << endl;
            abort();
        default:
            break;
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);

    QGuiApplication app(argc, argv);

    // register my own image provider
    // MyImageProvider *imageProvider = new MyImageProvider(QQmlImageProviderBase::Image);
    // QObject::connect(imageProvider, SIGNAL(valueChanged(int)), imageProvider, SLOT(setValue(int)));

    QQmlApplicationEngine engine;
    //engine.addImageProvider("myprovider", imageProvider);
    engine.rootContext()->setContextProperty("core", NowPlayingCore::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
