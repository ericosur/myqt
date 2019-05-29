#ifndef __COMMON_TEST_H__
#define __COMMON_TEST_H__

#include <QDir>
#include <QString>
#include <QStringList>

void print_title(const char* title);
void print_sep();

QString check_name(const QStringList& sl, const QString& key);
void no_conflict_name();
void unicode_char();

bool try_path(const QString& _home, QDir& _dir);
void test_arg_format();
QString toPercentEncoding(const QString& str);
QString doSanity(const QString& str);
void test__pe();
void test_runscript();
void run_default_tests();

#endif  // __COMMON_TEST_H__
