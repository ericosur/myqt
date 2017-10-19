/**
    \file main.cpp
    \brief entry point and test function
**/

#include <QtCore>
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>
#include <QTime>
#include <QTextCodec>
#include <QUrl>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

#include "commonutil.h"
#include "handleopt.h"


int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);

    handleopt(argc, argv);

    return 0;
}
