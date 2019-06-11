#include "seqcore.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>
#include <QDebug>


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    SeqCore* c = SeqCore::getInstance();
    c->test();


    return 0;
}
