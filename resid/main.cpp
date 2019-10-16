#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include <iostream>

#include "residutil.h"
#include "strdef.h"
#include "testcase.h"
#include "msgout.h"

//using namespace std;

QList<QString> namelist = {
    "alpha", "bravo", "charlie", "delta", "echo"
};

void test_list()
{
    foreach (const QString &item, namelist) {
        qDebug() << item;
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // default to on
    g_messageVerbose = true;
    qInstallMessageHandler(myMessageOutput);
    qDebug() << "string resid testing...";

    if (argc > 1 && strcmp(argv[1],"-v")==0) {
        std::cout << "verbose mode on\n";
        g_messageVerbose = true;
    }

    //test_cache();
    test_list();

    return 0;
}
