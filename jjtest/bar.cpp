#include <QString>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <iostream>

void test_hex_to_int()
{
    using namespace std;
    cout << "test " << __func__ << "===>" << endl;
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

QStringList test_split()
{
    qDebug() << "test " << __func__ << "===>";
    QString input = "mp4|mpg|wav|avi|mkv";
    QStringList filterlist = input.split("|");

    for (QString s: filterlist) {
        qDebug() << s;
    }

    return filterlist;
}

void test_bar()
{
    //test_hex_to_int();
    //json_parse_test();
    qDebug() << test_split();
}
