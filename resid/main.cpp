#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include <iostream>

#include "residutil.h"
#include "strdef.h"
#include "testcase.h"
#include "msgout.h"

//using namespace std;

void test_all()
{

}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    g_messageVerbose = false;
    qInstallMessageHandler(myMessageOutput);
    qDebug() << "string resid testing...";

    if (argc > 1 && strcmp(argv[1],"-v")==0) {
        std::cout << "verbose mode on\n";
        g_messageVerbose = true;
    }

    test_cache();

    return 0;
}
