/// \file main.cpp
///

#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "foo.h"
#include "bar.h"


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test_hex_to_int();
    json_parse_test();

    test();

    return 0;
}
