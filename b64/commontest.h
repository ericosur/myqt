#ifndef __COMMON_TEST_H__
#define __COMMON_TEST_H__

#include <stdio.h>
#include <string.h>

#include <QString>
#include <QStringList>
#include <QDir>
#include <QUrl>
#include <QProcess>

#include <QDebug>

void print_title(const char* title);
void print_sep();

QString check_name(const QStringList& sl, const QString& key);
void no_conflict_name();

bool try_path(const QString& _home, QDir& _dir);
void test_arg_format();
QString toPercentEncoding(const QString& str);
QString doSanity(const QString& str);
void test__pe();
void test_runscript();

#endif  // __COMMON_TEST_H__
