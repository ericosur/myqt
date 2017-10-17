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

public:
    bool bSelectAll = false;
    bool bDebug = false;
    bool bQueryViaInternet = false;
    QString sFilename;
    QString sConfig;
    QString sOutfile;
    QString sOutconfig;
};



#endif  // __UTIL_VARS_H__
