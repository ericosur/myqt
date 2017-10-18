#include <iostream>
#include <iomanip> // for std::setw
#include "json.hpp"

using json = nlohmann::json;

bool parse_and_dump(const char* text, json& result)
{
    // parse and serialize JSON
    result = json::parse(text);
    //std::cout << std::setw(4) << j_complete << "\n\n";

    return true;
}

int test_parse_string()
{
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

    if ( parse_and_dump(text, myobj) ) {
        std::cout << std::setw(4) << myobj << "\n\n";
        return true;
    }
    return false;
}

