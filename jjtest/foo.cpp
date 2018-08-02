#include "foo.h"
#include "readjson.h"

#include "nlohmann/json.hpp"
#include <QFile>
#include <QDebug>

#define DATAJSON    "../../json/all.json"

//using namespace std;
using namespace nlohmann;

void to_json(json& j, const Person& p)
{
    j = json{
        {"name", p.getName()},
        {"address", p.getAddress()},
        {"age", p.getAge()}
    };
}

void from_json(const json& j, Person& p)
{
    p.setName( j.at("name").get<std::string>() );
    p.setAddress( j.at("address").get<std::string>() );
    p.setAge( j.at("age").get<int>() );
}

void test_foo()
{
    //Person p = {"Alice Smith", "Taipei City", 30};
    Person p;
    p.setName("Alice Smith");
    p.setAddress("Taipei City");
    p.setAge(30);

    // convert **Person** to **json**
    json j = p;
    cout << j << endl;
    // convert **json** to **p2**
    Person p2 = j;

    assert(p == p2);
}

void test_bar()
{
    // create an object from an object_t value
    json::object_t object_value = { {"one", 1}, {"two", 2} };
    json j_object_t(object_value);
    cout << "t_object_t: " << j_object_t.dump(4) << endl;

    // create an object from std::map
    std::map<std::string, int> c_map
    {
        {"apple", 100}, {"whiskey", 300}, {"tiger", 250}
    };
    json j_map(c_map);
    cout << "c_map: " << j_map.dump(4) << endl;
    // string str = j_map.dump();
    // cout << "str: " << str << endl;
}

void test_weather()
{
    ifstream inf("../query.txt");
    json jj;
    inf >> jj;
    //cout << jj.dump(4) << endl;

    string created = jj["query"]["created"].get<string>();
    cout << "created: " << created << endl;

    map<string, string> condition = jj["query"]["results"]["channel"]["item"]["condition"].get<map<string, string>>();

    condition["hello"] = "world";

    for (map<string,string>::iterator it=condition.begin(); it!=condition.end(); ++it)
        cout << it->first << " => " << it->second << '\n';

    //cout << "temp:" << condition["temp"] << endl;

}

void test_qjson()
{
    qDebug() << Q_FUNC_INFO;
    QString fn = DATAJSON;
    ReadJson j(fn);
    if (!j.loadFile()) {
        qWarning() << "fail to load..." << fn;
        return;
    }
    //QJsonObject j = j.getJobject();
    qDebug() << j.getLeafString("query.results.channel.item.condition.text");
    //j["query"].toObject()["results"].toObject()["channel"]...["text"].toString()
}

void test_atxt_by_hpp()
{
    qDebug() << Q_FUNC_INFO;
    string json_file = DATAJSON;
    if (!QFile::exists(json_file.c_str())) {
        qDebug() << "file not found:" << json_file.c_str();
        return;
    }

    try {
        ifstream inf(json_file);
        json j;
        inf >> j;

        cout << j.at("query").at("results").at("channel").at("item").at("condition").at("text") << endl;
#if 0
        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            for (auto& e: j[it.key()]) {
                string key = it.key();
                cout << key << ": " << e << endl;
            }
        }
#endif
    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    } catch (json::out_of_range& e) {
        cout << "out_of_range:" << e.what() << endl;
    }
}

void test_atxt()
{
    qDebug() << "using Qt json...";
    test_qjson();
    qDebug() << "using json.hpp...";
    test_atxt_by_hpp();
}

void test_obj()
{
    qDebug() << Q_FUNC_INFO;
    string json_file = "notexist.json";

    cout << "read " << json_file << endl;
    try {
        ifstream inf(json_file);
        json j;
        inf >> j;

        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            for (auto& e: j[it.key()]) {
                string key = it.key();
                cout << key << ": " << e << endl;
            }
        }
    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    }
}

string get_from_id(const string& msgid)
{
    string json_file = "../strdef.json";
    cout << "read " << json_file << endl;
    try {
        ifstream inf(json_file);
        json jj;
        inf >> jj;

        string id = jj.at("General").at(msgid);
        string foo = jj.at("ar_AE").at(id);

        return foo;
    } catch (json::out_of_range& e) {
       std::cout << "out of range:" << e.what() << '\n';
    }

    return "";
}

void test_addon()
{
    string json_file = "../apps-add-ons.json";
    cout << "read " << json_file << endl;
    try {
        ifstream inf(json_file);
        json j;
        inf >> j;

        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            json item = (*it);
            cout << item.at("name") << endl
                << item.at("icon") << endl;
        }
    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    }
}

void test()
{
    // test_foo();
    // cout << endl;
     test_bar();
     cout << endl;
    //test_weather();

    test_atxt();
    cout << "ok" << endl;

    //test_addon();
}
