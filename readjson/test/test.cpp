#include "test.h"

#include <QStringList>
#include <QDateTime>
#include <QFile>

#define JSON_READ       "input.json"
#define JSON_WRITE      "foo.json"

QString json_string;

const QHash<QString, const char*> AppJsonTable = {
    {"Radio", "radio.json"},
    {"CdMusic", "cdmusic.json"},
    {"A2DP", "a2dp.json"},
    {"UsbMusic", "usbmusic.json"},
    {"Ipod", "ipod.json"},
    {"AUX", "aux.json"},
};

QString loadJsonAsString(const QString& fn)
{
    //qDebug() << __PRETTY_FUNCTION__;
    QString old_str = json_string;
    QJsonObject jo;
    if (ReadJson::loadFile(fn, jo)) {
        jo.remove("duration");
        jo.remove("msecsSinceEpoch");
        jo.remove("position");
        QString jstr = QJsonDocument::fromVariant(jo.toVariantMap()).toJson();
        qDebug() << "jstr:" << jstr;
        if (jstr == old_str) {
            qDebug() << "loadJsonAsString: same, will not update";
        } else {
            //NowPlayingCore::getInstance()->setJsonstring(jstr);
            json_string = jstr;
        }
        return jstr;
    }
    qWarning() << "loadJson(): something wrong";
    return QString();
}

class TestJson
{
public:
    TestJson();

    void init();
    void go();
    void testList();
    void testSet();
    void multitest();

    void filetest();
    void maptest();

private:
    bool isOk = false;
    ReadJson readjson;
};

TestJson::TestJson()
{
    //init();
}

void TestJson::init()
{
    if (!readjson.loadFile(JSON_READ)) {
        qDebug() << "[ERROR] failed to load json file";
        return;
    }
    isOk = true;
}

QVariant getJson(const QString& fn) {
    QFile file(fn);
    if(!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "smt wrong!";
        return QVariant();
    }
    QString s = file.readAll();
    file.close();
    QVariant v = QJsonDocument::fromJson(s.toUtf8()).toVariant();
    qDebug() << __PRETTY_FUNCTION__ << v;
    return v;
}

void TestJson::filetest()
{
    QString f = "/home/rasmus/test/media.json";
#if 1
    QJsonObject j;

    j["test"] = "value";
    j["name"] = "abcdefg";
    ReadJson::saveFile(f, j);
    qDebug() << j;
#endif
    qDebug() << __PRETTY_FUNCTION__;
    getJson(f);
}

void TestJson::maptest()
{
    QString s = AppJsonTable["nosuch"];
    if (s.isEmpty()) {
        qDebug() << "nosuch";
    }
    loadJsonAsString("../usbmusic.json");
}

void TestJson::go()
{
    //testSet();
    //filetest();
    maptest();
}

void TestJson::testSet()
{
    ReadJson *r = new ReadJson();
    r->loadFile("foo.json");

    r->setString("name", "foo.json");
    r->setString("title", "test json");
    r->setInt("val", 199);

    r->saveFile();
    delete r;

    ReadJson p;
    p.loadFile("foo.json");
    qDebug() << p.getString("name", "defaultname");
    qDebug() << p.getString("title", "defaulttitle");
    qDebug() << p.getString("description", "defaultdescription");
    qDebug() << p.getInt("val", 999);
    qDebug() << "out:" << p.getJobject();
}

void TestJson::multitest()
{
    qDebug() << Q_FUNC_INFO;
    QJsonObject json;
    ReadJson rj("input.json");

    if (!rj.loadFile()) {
        qWarning() << "[ERROR] load fail";
    } else {
        qDebug() << json;
    }

    int t = rj.getLeafValue("Music.musictime").toInt();
    qDebug() << "t:" << t;
    // t = rj.getLeafValue("Music.notexist").toInt();
    // qDebug() << "t:" << t;

    //json = rj.getJobject();
    //qDebug() << "dump json:\n" << json;
    //
    qint64 current = QDateTime::currentMSecsSinceEpoch();
    rj.setInt64("current", current);

    qint64 q = rj.getInt64("current", -1);
    qDebug() << "q:" << q;

    qDebug() << rj.getLeafString("test.first.astring", "nostring");
    qDebug() << rj.getLeafInt("test.first.aint", 999);
    qDebug() << rj.getLeafBool("test.first.abool", true);
    qDebug() << rj.getLeafInt64("test.first.aint64", -1);

    qDebug() << rj.getLeafString("Picture.Source", "nostring");
    // query some keys that is not existed
#if 0
    QString str = rj.getString("name", "qwert");
    qDebug() << "str:" << str;
    rj.setString("name", "hello_world");
    qDebug() << "getString:" << rj.getString("name", "qwert");

    bool isExist = rj.getBool("isexist", true);
    qDebug() << "isExist:" << isExist;
    rj.setBool("isExist", false);
    qDebug() << "getBool:" << rj.getBool("isExist", true);

    int nosuchint = rj.getInt("nosuchint", 97);
    qDebug() << "nosuchint:" << nosuchint;
    rj.setInt("nosuchint", 101);
    qDebug() << "getInt:" << rj.getInt("nosuchint", 999);
#endif
    rj.saveFile();

}

void TestJson::testList()
{
    QJsonObject g
    {
        {"property1", 1},
        {"property2", 2}
    };

    QJsonObject json;
    json["General"] = g;
    ReadJson::saveFile(JSON_WRITE, json);
}

QString formatFreq(const QString& freq)
{
    qDebug() << __PRETTY_FUNCTION__ << "frq:" << freq;
    int f = freq.toInt();
    int lhs = f / 100;
    int rhs = f % 100;
    QString ret = QString("%1.%2").arg(lhs).arg(int(rhs),2,10,QLatin1Char('0'));
    qDebug() << ret;
    return ret;
}

void test()
{
    QStringList sl;
    sl << "apple" << "ball" << "cat" << "dog";
    ReadJson j;
    j.setLeafArray("fruit", sl);
    j.saveFile("fuck.json");
}

void test1()
{
    qDebug() << "hello world";

    TestJson foo;
    foo.go();
    //foo.testList();

    formatFreq("0");
    formatFreq("15");
    formatFreq("95");
    formatFreq("197");
    formatFreq("597");
    formatFreq("990");
    formatFreq("997");
    formatFreq("5480");
    formatFreq("6988");
    formatFreq("10750");
    formatFreq("10755");
}
