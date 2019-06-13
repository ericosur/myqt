#include "core.h"
// qtlib
#include "trypath.h"

#include <nlohmann/json.hpp>

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
}

void Core::dump()
{
    qDebug() << Q_FUNC_INFO << endl
        << "bDebug:" << bDebug << endl
        << "kTest:" << kTest << endl
        << "prepare_length:" << prepare_length << endl
        << "prepare_fill:" << prepare_fill << endl
        << "prepare_fn:" << prepare_fn.c_str() << endl
        << "corrupt_length:" << corrupt_length << endl
        << "corrupt_count:" << corrupt_count << endl
        << "corrupt_byte:" << corrupt_byte << endl
        << "read_fn:" << read_fn.c_str();


    qDebug() << "action list ==>";
    for (size_t i=0; i<v.size(); ++i) {
        qDebug() << v.at(i).c_str();
    }
}


void Core::read_config()
{
    QStringList pl;
    pl << "./" << "../" << getHomepath();
    QString result;
    if (!searchFileFromList(pl, "setting.json", result)) {
        qWarning() << "cannot find setting.json, abort...";
        exit(EXIT_REASON_ERROR);
    }

    std::string fn = result.toUtf8().data();
    std::fstream fin(fn);
//nlohmann::json
    nlohmann::json j;

    CHECK_IF_DEBUG( qDebug() << "read config from:" << fn.c_str() );

    try {
        fin >> j;
        prepare_length = j.at("prepare").at("length");
        prepare_fill = j.at("prepare").at("fill");
        prepare_fn = j.at("prepare").at("filename");
        corrupt_length = j.at("corrupt").at("block").at("length");
        corrupt_count = j.at("corrupt").at("block").at("count");
        corrupt_byte =  j.at("corrupt").at("byte");
        read_fn = j.at("read").at("filename");
        v = j.at("action").get<std::vector<std::string>>();
    } catch (nlohmann::json::parse_error& e) {
        qDebug() << "json parse error:" << e.what();
        exit(EXIT_REASON_ERROR);
    } catch (nlohmann::json::out_of_range& e) {
        qDebug() << "json no such value:" << e.what();
        exit(EXIT_REASON_ERROR);
    }
    qDebug() << __func__ << "ok";
}

std::string Core::write_prepare_fn()
{
    FILE* fp = fopen(prepare_fn.c_str(), "wb");
    if (fp == nullptr) {
        qWarning() << "cannot write file, abort...";
        exit(EXIT_REASON_ERROR);
    }

    for (size_t i = 0; i < prepare_length; ++i) {
        fputc(prepare_fill, fp);
    }

    fclose(fp);
    return prepare_fn;
}

void Core::do_corrupt(const std::string& fn)
{
    FILE* fp = fopen(fn.c_str(), "r+b");
    CHECK_IF_DEBUG( qDebug() << "do corrupt on file:" << fn.c_str() );
    if (fp == nullptr) {
        qWarning() << "cannot read file for writing, abort...";
        exit(EXIT_REASON_ERROR);
    }
    int random_pos = 20;
    fseek(fp, random_pos, SEEK_SET);
    fputc(corrupt_byte, fp);
    fclose(fp);
}

std::string Core::read_file()
{
    CHECK_IF_DEBUG( qDebug() << __func__ << read_fn.c_str() );
    if ( try_read(read_fn) ) {
        return read_fn;
    }
    return "";
}

bool Core::try_read(const std::string& fn)
{
    bool result = false;
    CHECK_IF_DEBUG( qDebug() << __func__ << fn.c_str() );
    std::fstream fin(read_fn);
    nlohmann::json k;
    try {
        fin >> k;
        result = true;
    } catch (nlohmann::json::parse_error& e) {
        qWarning() << "read_file: parse_error:" << e.what();
        result = false;
    }
    return result;
}

void Core::action()
{
    read_config();
    dump();

    qDebug() << "start action =====>";
    std::string fn;
    for (size_t i=0; i<v.size(); ++i) {
        QString act = v.at(i).c_str();
        CHECK_IF_DEBUG( qDebug() << "=====>" << act );
        if (act == "read") {
            fn = read_file();
            if (fn == "") {
                qWarning() << "already corrupted";
            }
        } else if (act == "prepare") {
            fn = write_prepare_fn();
        } else if (act == "corrupt") {
            do_corrupt(fn);
        }
    }
}

