#include <iostream>

#include "utilvars.h"
#include "commonutil.h"

#include "json.hpp"
using json = nlohmann::json;
bool parse_and_dump(const char* text, json& result);


UtilVars* UtilVars::_instance = NULL;
UtilVars* UtilVars::getInstance()
{
    if (_instance == NULL) {
        _instance = new UtilVars();
    }
    return _instance;
}

UtilVars::UtilVars()
{

}

void UtilVars::dumpVars()
{
    qDebug() << __func__ << "=====>" << endl
        << "-a: SelectAll:" << bSelectAll << endl
        << "-b [strid]: query resid:" << sStrid << endl
        << "-c: Configfile:" << sConfig << endl
        << "-d: Debug:" << bDebug << endl
        << "-f: Filename:" << sFilename << endl
        << "-g: Dump config to file:" << sOutconfig << endl
        << "-j: Test json.hpp:" << bTestjsonhpp << endl
        << "-o: Outfile:" << sOutfile << endl
        << "-q: QueryViaInternet:" << bQueryViaInternet << endl
        << "<=====";
}

void UtilVars::fill_object(QJsonObject& obj)
{
    QJsonObject app;
    app["bSelectAll"] = bSelectAll;
    app["bDebug"] = bDebug;
    app["sFilename"] = sFilename;
    app["sOutfile"] = sOutfile;
    app["bQueryViaInternet"] = bQueryViaInternet;
    app["sConfig"] = sConfig;
    app["sOutconfig"] = sOutconfig;
    app["bTestjsonhpp"] = bTestjsonhpp;
    app["bQueryResid"] = bQueryResid;
    app["sStrid"] = sStrid;

    QJsonObject foo;
    foo["name"] = "Batman";
    foo["height"] = 200;
    foo["male"] = true;

    obj["app"] = app;
    obj["extra"] = foo;
}

void UtilVars::fill_object_jsonhpp()
{
    qDebug() << Q_FUNC_INFO;
    json obj = {
        {"app",
            {
                {"bSelectAll", bSelectAll},
                {"bDebug", bDebug},
                {"sFilename", sFilename.toUtf8().data()},
                {"sOutfile", sOutfile.toUtf8().data()},
                {"bQueryViaInternet", bQueryViaInternet},
                {"sConfig", sConfig.toUtf8().data()},
                {"sOutconfig", sOutconfig.toUtf8().data()},
                {"bTestjsonhpp", bTestjsonhpp}
            }
        },
        {"extra", {}}
    };

    obj["app"]["test"] = "hello";

    json extra = {
        {"name", "wonder woman"},
        {"height", 185},
        {"weight", 60},
        {"power", 100}
    };
    obj["extra"] = extra;
    obj["extra"]["def"] = 99;

    qDebug() << obj.dump(2).c_str();
}

bool UtilVars::dumpConfig()
{
    QString _fn = DEFAULT_CONFIGFILE;
    if (!sOutconfig.isEmpty()) {
        _fn = sOutconfig;
    }
    QFile saveFile(_fn);
    //qDebug() << __func__ << _fn;
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "fail to open file for writing:" << _fn;
        return false;
    }

    QJsonObject obj;
    fill_object(obj);
    QJsonDocument saveDoc(obj);
    saveFile.write(saveDoc.toJson());

    fill_object_jsonhpp();

    return true;
}

// bool UtilVars::dump_config_by_jsonhpp()
// {

// }

bool UtilVars::read_config_by_jsonhpp()
{
    qDebug() << Q_FUNC_INFO;

    QByteArray arr;
    if ( readFileToByteArray(arr, sConfig) ) {
        //arr.append("\"");
        qDebug() << "calling parse_and_dump:";
        json result;
        try {
            parse_and_dump(arr.data(), result);

            QString s = result["extra"]["name"].get<std::string>().c_str();
            qDebug() << "extra name:" << s;
            int i = result["extra"]["height"].get<int>();
            qDebug() << "height:" << i;
            bool b = result["extra"]["male"].get<bool>();
            qDebug() << "is male:" << b;

        } catch (json::parse_error& e) {
            // output exception information
            std::cout << "message: " << e.what() << '\n'
                      << "exception id: " << e.id << '\n'
                      << "byte position of error: " << e.byte << std::endl;
        }


        //s = result["extra"].dump().get<std::string>().c_str();
        //writeStringToFile(result.dump(4).c_str(), "/tmp/f.dump");
    }

    return true;
}

bool UtilVars::read_config_by_readjson()
{
    ReadJson _conf(sConfig);
    if (!_conf.loadFile()) {
        return false;
    }

    QJsonObject o = _conf.getLeafObject("app");
    bDebug = o["bDebug"].toBool();
    bQueryViaInternet = o["bQueryViaInternet"].toBool();
    bSelectAll = o["bSelectAll"].toBool();
    sFilename = o["sFilename"].toString();
    sOutfile = o["sOutfile"].toString();
    sOutconfig = o["sOutconfig"].toString();
    bTestjsonhpp = o["bTestjsonhpp"].toBool();
    return true;
}

bool UtilVars::readConfig()
{
    if (sConfig.isEmpty() || !QFile::exists(sConfig)) {
        return false;
    }

    bool ret = read_config_by_readjson();

    // another test
    read_config_by_jsonhpp();

    return ret;
}
