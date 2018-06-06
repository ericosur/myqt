#ifndef __JSON_UTIL_H__
#define __JSON_UTIL_H__

#include <iostream>
#include <iomanip> // for std::setw
#include <nlohmann/json.hpp>

bool parse_and_dump(const char* text, nlohmann::json& result);

#endif  // __JSON_UTIL_H__
