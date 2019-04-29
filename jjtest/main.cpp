/// \file main.cpp
///

#include <QCoreApplication>
#include <QString>
#include <QDebug>

#include "foo.h"

int json_parse_test();

void test_hex_to_int()
{
    const int VALUE = 0x1A2B;
    bool ok = false;

    Q_ASSERT(QString("0x1A2B").toInt(&ok, 16) == VALUE);
    Q_ASSERT(QString("0x1a2b").toInt(&ok, 16) == VALUE);
    Q_ASSERT(QString("1a2B").toInt(&ok, 16) == VALUE);
    //Q_ASSERT(QString("x1A4b").toInt(&ok, 16) == VALUE);
    //Q_ASSERT(QString("x1a4b").toInt(&ok, 16) == VALUE);

    Q_ASSERT(QString::number(VALUE, 16).toUpper() == QString("1A2B"));
    Q_ASSERT(QString::number(VALUE, 16) == QString("1a2b"));
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test_hex_to_int();
    json_parse_test();

    return 0;
}
