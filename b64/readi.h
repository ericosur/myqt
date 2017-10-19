#ifndef __READ_INI_H__
#define __READ_INI_H__

#include <QString>
#include <QSettings>
#include <QFile>
#include <QDebug>

#define INIPATH     "/home/rasmus/src/myqt/b64/fake.ini"
#define JSONPATH    "/home/rasmus/src/myqt/b64/fake.json"

void test_read_config();
void test_read_ini();
void test_read_json();

#endif // __READ_INI_H__
