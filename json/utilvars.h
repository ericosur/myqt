#ifndef __UTIL_VARS_H__
#define __UTIL_VARS_H__

#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include "readjson.h"

#define DEFAULT_CONFIGFILE    "config.json"
#define DEFAULT_DUMPCONFIG    "/tmp/mydumpconfig.json"

class UtilVars
{
public:
    static UtilVars* getInstance();
    void dumpVars();
    bool dumpConfig();
    bool readConfig();

protected:
    static UtilVars* _instance;
    UtilVars();

private:
    void fill_object(QJsonObject& obj);
    bool read_config_by_jsonhpp();
    bool read_config_by_readjson();

    void fill_object_jsonhpp();

public:
    bool bSelectAll = false;
    bool bDebug = false;
    bool bQueryViaInternet = false;
    QString sFilename;
    QString sConfig;
    QString sOutfile;
    QString sOutconfig;
    bool bTestjsonhpp = false;
};



#endif  // __UTIL_VARS_H__
