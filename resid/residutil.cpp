/// \file residutil.cpp
/// it is former testmsg.cpp

#include "residutil.h"
#include "strdef.h"

//#define USE_INI_METHOD

#include <QRegExp>
#define STRING_NULL    ""
#define bDebug true

QString findFileLocation(const QString& fn)
{
    QStringList findlist;

#ifdef USE_YOSETARGET
    findlist << "/usr/share"
        << "/data/apps"
        << "/data"
        << "/misc"
        << "/tmp";
#else
    findlist << QDir::currentPath()
             << QDir::homePath()
             << QDir::tempPath();
#endif

    foreach (QString ph, findlist) {
        QString fullpath = QString("%1%2%3").arg(ph)
                                .arg(QDir::separator())
                                .arg(fn);
        if (QFile::exists(fullpath)) {
            return fullpath;
        }
    }

    return "";
}


#ifdef USE_INI_METHOD

class IniCache : public QObject
{
public:
    static IniCache* getInstance() {
        if (_instance == NULL) {
            _instance = new IniCache();
        }
        return _instance;
    }
    QSettings* getSettings() {
        return ini_settings;
    }
    bool checkLocale(const QString& loc) {
        return locale_lists.contains(loc);
    }
    bool checkStrid(const QString& strid) {
        return stringid_lists.contains(strid);
    }

protected:
    IniCache();
    static IniCache* _instance;

private:
    QSettings* ini_settings = NULL;
    QStringList stringid_lists;
    QStringList locale_lists;
};

IniCache* IniCache::_instance = NULL;
IniCache::IniCache()
{
    QString fn = findFileLocation(STRMSGINI);
    if (bDebug)
        qDebug() << "ini file from:" << fn;
    if (fn == "") {
        qWarning() << "[FATAL] string id INI not found...";
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    ini_settings = new QSettings(fn, QSettings::IniFormat);
    ini_settings->setIniCodec(codec);

    locale_lists = ini_settings->childGroups();
    qDebug() << "locale_lists:" << locale_lists;

    ini_settings->beginGroup("/");
    stringid_lists = ini_settings->childKeys();
    ini_settings->endGroup();
}


QString getStringByIntid(const QString& locale_name, int id)
{
    if (bDebug)
        qDebug() << "getmsg(ini) locale:" << locale_name << ", id:" << id;

    IniCache* ich = IniCache::getInstance();
    QSettings* ini = ich->getSettings();
    if (ini == NULL) {
        qWarning() << "[FATAL] string id INI not found...";
        return STRING_NULL;
    }

    if (!ich->checkLocale(locale_name)) {
        qDebug() << "[ERROR] getmsg(ini) no such locale:" << locale_name;
        return STRING_NULL;
    }
    if (id > STRING_MAXSTRID || id < STRING_MINSTRID) {
        qDebug() << "[ERROR] getmsg(ini) id exceed boundary:" << id;
        return STRING_NULL;
    }

    QString key = QString("/%1/%2").arg(locale_name).arg(id);
    if (bDebug)
        qDebug() << "key:" << key;
    QString tmp = ini->value(key, STRING_NULL).toString();
    return tmp;
}

QString getStringByStrid(const QString& locale_name, const QString& strid)
{
    if (bDebug)
        qDebug() << "getmsg(ini) locale:" << locale_name << ", strid:" << strid;

    IniCache* ich = IniCache::getInstance();
    QSettings* ini = IniCache::getInstance()->getSettings();
    if (ini == NULL) {
        qWarning() << "[FATAL] string id INI not found...";
        return STRING_NULL;
    }
    if (!ich->checkLocale(locale_name)) {
        qDebug() << "[ERROR] getmsg(ini) no such locale:" << locale_name;
        return STRING_NULL;
    }
    if (!ich->checkStrid(strid)) {
        qDebug() << "[ERROR] getmsg(ini) no such stringid:" << strid;
        return STRING_NULL;
    }
    // if caller use integer id like 10001
    QRegExp re("\\d+");
    if (re.exactMatch(strid)) {
        int id = strid.toInt();
        return getStringByIntid(locale_name, id);
    }

    QString key = QString("/%1").arg(strid);
    int numid = ini->value(key, -1).toInt();
    return getStringByIntid(locale_name, numid);
}

#else   // USE_INI_METHOD

#include <QCache>
#include <iostream>
#include <fstream>
#include <string>

#ifdef USE_YOSETARGET
#include <json.hpp>
#else
#include <nlohmann/json.hpp>
#endif

using namespace std;
using namespace nlohmann;

class JsonCache : public QObject
{
public:
    static JsonCache* getInstance() {
        if (_instance == NULL) {
            _instance = new JsonCache();
        }
        return _instance;
    }
    json& getJson() {
        return _jj;
    }
    bool isOpen() {
        return isOk;
    }
    bool checkLocale(const QString& loc) {
        return locale_lists.contains(loc);
    }
    bool checkStrid(const QString& strid) {
        return stringid_lists.contains(strid);
    }
    QString getLastLocale() const {
        return last_locale;
    }
    void setLastLocale(const QString& loc) {
        if (checkLocale(loc)) {
            last_locale = loc;
        }
    }
    int getHitCount() const {
        return hitCount;
    }

    void clearCache() {
        cache.clear();
        if (bDebug)
            qDebug() << "[json cache] cache cleared" << cache.totalCost();
    }
    void insertCache(const QString& key, const QString& val) {
        //qDebug() << __PRETTY_FUNCTION__;
        sptr = new QString(val);
        bool ret = cache.insert(key, sptr);
        if (ret) {
            if (bDebug)
                qDebug() << "[json cache] insert cache ok"
                    << key << "," << val
                    << cache.totalCost();
        }
    }
    QString queryCache(const QString& key) {
        //qDebug() << __PRETTY_FUNCTION__;
        QString* q = cache.object(key);
        if (q == NULL) {
            if (bDebug)
                qDebug() << "[json cache] not found from cache:" << key;
            return QString();
        }
        QString ret = *q;
        hitCount ++;
        if (bDebug)
            qDebug() << "[json cache] cache hit:" << key << "," << ret;
        return ret;
    }

    void test();

protected:
    JsonCache();
    static JsonCache* _instance;
    void load_locale_list();

private:
    QStringList locale_lists;
    QStringList stringid_lists;

    json _jj;
    bool isOk = false;

    QString *sptr = NULL;
    QString last_locale;
    QCache<QString, QString> cache;
    int hitCount = 0;
};

JsonCache* JsonCache::_instance = NULL;
JsonCache::JsonCache()
{
    QString fn = findFileLocation(STRMSG_JSONFILE);
    if (bDebug) {
        qDebug() << "getmsg(json): found at:" << fn;
    }
    if (fn == "") {
        qWarning() << "[FATAL] no string id JSON...";
        isOk = false;
        return;
    }

    string _fn = fn.toUtf8().data();
    ifstream inf(_fn);

    try {
        inf >> _jj;
        isOk = true;
        load_locale_list();
    } catch (nlohmann::json::exception& e) {
        // output exception information
        std::cout << "[ERROR] message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n';
        isOk = false;
    }

    cache.setMaxCost(120);
}

void JsonCache::load_locale_list()
{
    // iterate the array
    for (json::iterator it = _jj.begin(); it != _jj.end(); ++it) {
        //std::cout << it.key() << '\n';
        QString tok = it.key().c_str();
        if (tok != "General") {
            locale_lists << tok;
        }
    }
    try {
        json jp = _jj.at("General");
        for (json::iterator it = jp.begin(); it != jp.end(); ++it) {
            //std::cout << it.key() << '\n';
            QString tok = it.key().c_str();
            stringid_lists << tok;
        }
    } catch (nlohmann::json::exception& e) {
        // output exception information
        std::cout << "[ERROR] message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n';
        isOk = false;
    }
}

JsonCache* json_basic_check(const QString& locale_name)
{
    JsonCache* jc = JsonCache::getInstance();
    if (jc == NULL) {
        qWarning() << "[FATAL] JsonCache is NULL!";
        return NULL;
    }
    if (!jc->isOpen()) {
        qWarning() << "[ERROR] json is not open...";
        return NULL;
    }
    if (!jc->checkLocale(locale_name)) {
        qWarning() << "[ERROR] no such locale:" << locale_name;
        return NULL;
    } else {
#if 0
        if (locale_name != jc->getLastLocale()) {
            if (bDebug)
                qDebug() << "[INFO] locale changes...";
            jc->clearCache();
            jc->setLastLocale(locale_name);
        }
#endif
    }
    return jc;
}

QString getStringByIntid(const QString& locale_name, int id)
{
    if (bDebug)
        qDebug() << __func__ << "getmsg(json) locale:" << locale_name << ", id:" << id;

    JsonCache* jc = json_basic_check(locale_name);
    if (jc == NULL) {
        return STRING_NULL;
    }
    if (id > STRING_MAXSTRID || id < STRING_MINSTRID) {
        if (bDebug)
            qDebug() << "[ERROR] getmsg(json) id exceed boundary:" << id;
        return STRING_NULL;
    }

    try {
        json jj = jc->getJson();
        string _locale = locale_name.toUtf8().data();
        string msg = jj[_locale].at(to_string(id));
        return QString(msg.c_str());
    } catch (nlohmann::json::exception& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n';
    }
    return "";
}

QString getStringByStrid(const QString& locale_name, const QString& strid)
{
    Q_UNUSED(locale_name);
    Q_UNUSED(strid);

    JsonCache* jc = json_basic_check(locale_name);
    if (jc == NULL) {
        return STRING_NULL;
    }

    if (!jc->checkStrid(strid)) {
        qDebug() << "[ERROR] no such stringid";
        return STRING_NULL;
    }
    if (bDebug)
        qDebug() << "cache hitCount: " << jc->getHitCount();
    QString cacheid = QString("%1.%2").arg(locale_name).arg(strid);
    QString _tmp_ = jc->queryCache(cacheid);
    if (!_tmp_.isEmpty()) {
        return _tmp_;
    }
    if (bDebug)
        qDebug() << "getStringByStrid: look up from table";
    try {
        json jj = jc->getJson();
        if (bDebug) {
            qDebug() << "local:" << locale_name << "strid:" << strid;
        }

        string _locale = locale_name.toUtf8().data();
        string id;

        // if caller use integer id like 10001
        QRegExp re("\\d+");
        if (re.exactMatch(strid)) {
            id = strid.toUtf8().data();
        } else {
            string _strid = strid.toUtf8().data();
            id = jj.at("General").at(_strid);
        }

        int Intid = QString(id.c_str()).toInt();
        if (Intid > STRING_MAXSTRID || Intid < STRING_MINSTRID) {
            qDebug() << "[ERROR] getmsg(json) id exceed boundary:" << Intid;
            return STRING_NULL;
        }

        string msg = jj[_locale].at(id);
        QString ans = QString(msg.c_str());
        jc->insertCache(cacheid, ans);
        return ans;
    } catch (nlohmann::json::exception& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n';
    }
    return "";
}

#endif  // USE_INI_METHOD

