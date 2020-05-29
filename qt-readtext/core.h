#ifndef __COMMON_CORE__H__
#define __COMMON_CORE__H__

#include <string>

#define SETTING_JSON_FILE   "setting.json"

class Core
{
public:
    Core();

    void parse_string(const std::string& s);
    bool read_setting();
    bool read_file(const std::string& fn);

    std::string get_setting_filename() {
        return setting_file;
    }
    std::string get_data_filename() {
        return data_file;
    }

private:
    std::string setting_file = SETTING_JSON_FILE;
    std::string data_file;

    std::string value_list;
};



#endif  // __COMMON_CORE__H__
