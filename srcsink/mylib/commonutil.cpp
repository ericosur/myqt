/**
    \file commonutil.cpp
    \brief implementation of myMessageOutput()
**/
#include "commonutil.h"

#include <QTime>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QString>
#include <QDebug>

#include <stdio.h>
#include <iostream>

#define YESNO(b)    ((b)?"yes":"no")


using namespace std;
bool g_messageVerbose = true;

/**
    \brief myMessageOutput() is customized message handler to redirect qDebug()
**/
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString txt;
    QString prefix = QString("[%1][%2] ")
                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                        .arg(qApp->applicationName());

    // special filter some messages
    if (msg.contains("Unable to fetch row")) {
        return;
    }

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
    }
}

QString md5sum(const char* buf, int size)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(buf, size);
    QString str_hash = hash.result().toHex().data();
    return str_hash;
}

void dump(unsigned char* buf, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        if (i && i%16==0)  printf("\n");
        printf("%02X ", buf[i]);
    }
    printf("\n");
}
