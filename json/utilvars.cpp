#include "utilvars.h"

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
        << "-c: Configfile:" << sConfig << endl
        << "-d: Debug:" << bDebug << endl
        << "-f: Filename:" << sFilename << endl
        << "-o: Outfile:" << sOutfile << endl
        << "-q: QueryViaInternet:" << bQueryViaInternet << endl
        << "<=====";
}

void UtilVars::fill_object(QJsonObject& obj)
{
    QJsonObject app;
    app["SelectAll"] = bSelectAll;
    app["Debug"] = bDebug;
    app["Filename"] = sFilename;
    app["Outfile"] = sOutfile;
    app["QueryViaInternet"] = bQueryViaInternet;
    app["Configfile"] = sConfig;

    QJsonObject foo;
    foo["name"] = "Batman";
    foo["height"] = 200;
    foo["male"] = true;

    obj["app"] = app;
    obj["extra"] = foo;
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

    return true;
}

bool UtilVars::readConfig()
{
    if (sConfig.isEmpty() || !QFile::exists(sConfig)) {
        return false;
    }

    ReadJson _conf(sConfig);
    if (!_conf.loadFile()) {
        return false;
    }

    //qDebug() << __func__;

    QJsonObject o = _conf.getLeafObject("app");
    bDebug = o["Debug"].toBool();
    bQueryViaInternet = o["QueryViaInternet"].toBool();
    bSelectAll = o["SelectAll"].toBool();
    sFilename = o["Filename"].toString();
    sOutfile = o["Outfile"].toString();

    return true;
}
