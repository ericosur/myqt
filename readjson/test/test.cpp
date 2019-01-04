#include "test.h"

#include <QStringList>
#include <QDateTime>

#define JSON_READ       "input.json"
#define JSON_WRITE      "foo.json"

class TestJson
{
public:
    TestJson();

    void init();
    void go();
    void testList();
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

void TestJson::go()
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

void test()
{
    qDebug() << "hello world";

    TestJson foo;
    foo.go();
    //foo.testList();

}
