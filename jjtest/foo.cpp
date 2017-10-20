#include "foo.h"
#include "json.hpp"

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
    cout << j_object_t.dump(4) << endl;

    // create an object from std::map
    std::map<std::string, int> c_map
    {
        {"one", 1}, {"two", 2}, {"three", 3}
    };
    json j_map(c_map);
    cout << j_map.dump(4) << endl;
}

void test_weather()
{
    ifstream inf("/home/rasmus/src/myqt/jjtest/a.txt");
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

string test_resid()
{
    try {
        ifstream inf("/home/rasmus/src/myqt/jjtest/strdef.json");
        json jj;
        inf >> jj;

        //string key = "MSG_WARNING";
        string key = "FUCK";
        string id = jj["General"].at(key);
        string foo = jj["ar_AE"].at(id);
        return foo;
    } /* catch (nlohmann::json::exception& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  ;
    } */
    catch (std::out_of_range)
   {
       std::cout << "out of range" << '\n';
   }
    return "";
}

void test()
{
    // test_foo();
    // cout << endl;
    // test_bar();
    // cout << endl;
    //test_weather();
    cout << test_resid() << endl;

    cout << "ok";
}
