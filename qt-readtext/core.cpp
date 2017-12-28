#include "core.h"
#include "json.hpp"

#include <QFile>
#include <iostream>
#include <fstream>

using namespace std;
using namespace nlohmann;

Core::Core()
{
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
