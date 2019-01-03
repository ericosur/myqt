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
    t = rj.getLeafValue("Music.notexist").toInt();
    qDebug() << "t:" << t;

    json = rj.getJobject();
    qDebug() << "json:" << json;
    qint64 current = QDateTime::currentMSecsSinceEpoch();
    json["current"] = current;

    ReadJson::saveFile("qq.json", json);
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
