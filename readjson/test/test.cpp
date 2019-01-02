#include "test.h"

#include <QStringList>

#define JSON_READ       "../mediaui.json"
#define JSON_WRITE      "../foo.json"

class TestJson
{
public:
    TestJson();

    void go();
    void testList();
private:
    bool isOk = false;
    ReadJson readjson;
};

TestJson::TestJson()
{
    if (!readjson.loadFile(JSON_READ)) {
        qDebug() << "[ERROR] failed to load json file";
        return;
    }
    isOk = true;
}

void TestJson::go()
{
    if (!isOk) {
        qDebug() << "failed";
        return;
    }

    readjson.setLeafValue("General.type", 299);
    readjson.setLeafValue("Music.musictime", 9801);
    readjson.setLeafValue("Music.isPlay", false);
    readjson.setLeafValue("Music.source", "file:///media/usb/storage/123.mp3");


    readjson.saveFile(JSON_WRITE);

    //qDebug() << __func__ << j;
    //ReadJson::saveFile(JSON_WRITE, j);
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
    //foo.go();
    foo.testList();

}
