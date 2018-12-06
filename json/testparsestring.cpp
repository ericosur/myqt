#include <iostream>
#include <iomanip> // for std::setw
#include <nlohmann/json.hpp>


bool parse_and_dump(const char* text, nlohmann::json& result)
{
    using json = nlohmann::json;
    // parse and serialize JSON
    result = json::parse(text);
    //std::cout << std::setw(4) << j_complete << "\n\n";

    return true;
}

int test_parse_string()
{
    using namespace std;
    using json = nlohmann::json;
    cout << __func__ << " uses a RAW string to initialize a json object\n";

    // a JSON text
    auto text = R"(
    {
        "Image": {
            "Width":  800,
            "Height": 600,
            "Title":  "View from 15th Floor",
            "Thumbnail": {
                "Url":    "http://www.example.com/image/481989943",
                "Height": 125,
                "Width":  100
            },
            "Animated" : false,
            "IDs": [116, 943, 234, 38793]
        }
    }
    )";
    json myobj;
    auto query = myobj.meta();
    cout << "json.hpp version: " << query["version"]["string"] << endl;

    if ( parse_and_dump(text, myobj) ) {
        cout << std::setw(4) << myobj << "\n\n";
        return true;
    }
    return false;
}
