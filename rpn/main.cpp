#include <QCoreApplication>
#include "foo.h"

void test()
{
    Foo foo;
    QStringList sl;

    sl << "3" << "2" << "1" << "+" << "*";
    foo.setRpn(sl);
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();


    return 0;
}
