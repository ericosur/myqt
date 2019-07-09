#include "mainwindow.h"

#include <iostream>
#include <QApplication>
#include <QTime>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString txt;
    QString prefix = QString("[%1][%2][%3] ")
                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                        .arg(qApp->applicationName())
                        .arg(qApp->applicationPid());

    using namespace std;
    switch (type) {
        case QtDebugMsg:
            txt = prefix + QString("D: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = prefix + QString("W: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = prefix + QString("C: %1").arg(msg);
            break;
        case QtInfoMsg:
            txt = prefix + QString("I: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = prefix + QString("F: %1").arg(msg);
            abort();
        default:
            break;
    }
    if (!txt.isEmpty()) {
        cout << txt.toUtf8().data() << endl;
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
