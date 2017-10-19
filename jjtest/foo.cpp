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
