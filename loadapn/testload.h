/// \file main.cpp
///

#ifndef __TEST_LOAD_H__
#define __TEST_LOAD_H__

#include <QObject>
#include <QList>
#include <QMap>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegularExpression>

typedef QList<QMap<QString, QString>> APN_List_Type;

class Solution : public QObject
{
public:
    Solution();
    ~Solution();

    void loadApnDatabase_old();
    void loadApnDatabase_new();

    void load_apn_re();
    void test_parse();
    QMap<QString, QString> parse_line(const QString& line);
    void load_apn1_file();

public:
    APN_List_Type apnList0;
    APN_List_Type apnList1;
    APN_List_Type apnList2;

private:
    QRegularExpression re;
    QFile apn1File;
    QTextStream textStream;
};

void test_load();

#endif  // __TEST_LOAD_H__
