#include "readi.h"
#include "commontest.h"

#include <QString>
#include <QSettings>
#include <QFile>
#include <QDebug>

#define INIPATH     "/home/rasmus/src/myqt/b64/fake.ini"
#define JSONPATH    "/home/rasmus/src/myqt/b64/fake.json"

void test_read_ini();
void test_read_json();


void show(const QString& dns, const QString& gw, const QString& ip)
{
    qDebug() << "dns:" << dns << endl
        << "gw:" << gw << endl
        << "ip:" << ip ;
}

void test_read_config()
{
    test_read_ini();
    test_read_json();
}

void test_read_ini()
{
    print_title(__func__);
    QString fn = INIPATH;
    if ( !QFile::exists(fn) ) {
        qWarning() << "ini not found:" << fn;
        return;
    }
    QSettings ini(fn, QSettings::IniFormat);
    QString dns = ini.value("DNS", "").toString();
    QString gw = ini.value("GW", "").toString();
    QString ip = ini.value("IP", "").toString();
    show(dns, gw, ip);
}

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

void test_read_json()
{
    print_title(__func__);
    try {
        std::ifstream infile(JSONPATH);
        nlohmann::json j;
        infile >> j;

        QString dns = j["DNS"].get<std::string>().c_str();
        QString gw = j["GW"].get<std::string>().c_str();
        QString ip = j["IP"].get<std::string>().c_str();
        show(dns, gw, ip);

    } catch (nlohmann::json::parse_error& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
    }

}
