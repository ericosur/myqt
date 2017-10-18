#include <iostream>
#include "json.hpp"

using namespace nlohmann;
using namespace std;

struct Person
{
    string name;
    string address;
    int age;
};

void to_json(json& j, const Person& p)
{
    j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

void from_json(const json& j, Person& p)
{
    p.name = j.at("name").get<std::string>();
    p.address = j.at("address").get<std::string>();
    p.age = j.at("age").get<int>();
}

void test_foo()
{
    Person p = {"Alice Smith", "Minli St., Taipei City", 30};
    json j = p;
    cout << j << endl;

    json k = {
        {"name", "Bob John"},
        {"address", "New York City"},
        {"age", 33}
    };
    Person p2 = k;
    cout << p2.name << endl;
}
