#include "core.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <QString>
#include <QStringList>
#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

using namespace std;
using namespace nlohmann;

Core::Core()
{
}

void Core::parse_string(const std::string& s)
{
    QString test = s.c_str();
    qDebug() << "parse_string:" << test;
    QStringList sl = test.split(",");
    bool ok = false;
    QJsonArray jarr;
    foreach (QString t, sl) {
        int v = t.toInt(&ok, 10);
        if (ok) {
            QJsonValue jv(v);
            jarr.push_back(jv);
        }
    }

    for (int i = 0; i < jarr.size(); i++) {
        qDebug() << jarr[i].toInt();
    }
}

bool Core::read_file(const string& fn)
{
    string json_file = fn;
    cout << "read setting from: " << json_file << endl;
    try {
        ifstream inf(json_file);
        json j;
        inf >> j;
/*
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            for (auto& e: j[it.key()]) {
                string key = it.key();
                cout << key << ": " << e << endl;
            }
        }
*/
        data_file = j.at("common").at("data_file");
        value_list = j.at("value_list");
        parse_string(value_list);
        return true;

    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    } catch (json::out_of_range& e) {
        cout << "out of range error:" << e.what() << endl;
    }

    return false;
}

bool Core::read_setting()
{
    string fn = SETTING_JSON_FILE;

    if (!QFile::exists(QString(fn.c_str()))) {
        fn = string("../") + fn;
    }
    bool ret = read_file(fn);

    return ret;
}
