#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

vector<string> get_vector_from_json(json& j, vector<string> keys)
{
    try {
        json kk = j;
        for (string i : keys) {
            kk = kk.at(i);
        }
        return kk.get<std::vector<string>>();
    } catch (json::type_error& e) {
        cout << "[F] type error:" << e.what() << endl;
    } catch (json::parse_error& e) {
        cout << "[F] parse error:" << e.what() << endl;
    } catch (json::out_of_range& e) {
        cout << "[F] out of range:" << e.what() << endl;
    }
    std::vector<string> v;
    return v;
}

int json_parse_test()
{
    char text[] = R"(
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
            "IDs": [
                "apple",
                "ball",
                "cat"
            ]
        }
    }
    )";

    // parse and serialize JSON
    json j = json::parse(text);
    //std::cout << std::setw(4) << j << endl;
    //cout << json.dump(4);
    // cout << j[".Image.Width"] << endl;
    // auto v = j["Image"]["IDs"].get<std::vector<int>>();
    // cout << v[0] << endl;
    // auto w = j.at("Image").at("IDs").get<std::vector<int>>();
    // cout << w[1] << endl;
    //cout << j.at("Image").at("IDs").get<std::vector<int>>();

    vector<string> keys;
    keys.push_back("Image");
    keys.push_back("IDs");
    std::vector<string> v = get_vector_from_json(j, keys);
    for (auto val: v) {
        cout << val << endl;
    }
    return 0;
}
