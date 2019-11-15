#include <QCoreApplication>
#include "foo.h"

void test()
{
    Foo::getInstance()->setRpn(QStringList(
        {"3", "2", "1", "+", "*"})
    );
    Foo::getInstance()->setRpn(QStringList(
        {"3", "5", "+", "7", "-", "2", "4", "*", "/"})
    );
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();

    return 0;
}
