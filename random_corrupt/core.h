#ifndef __CORE_H__
#define __CORE_H__

#include <QString>
#include <QDebug>

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

#include "util.h"

#define CHECK_IF_DEBUG(x)   \
    if (Core::getInstance()->bDebug) { \
        x; \
    }

class Core
{
public:
    static Core* getInstance();

    void action();

    void dump();
    void read_config();
    std::string write_prepare_fn();
    void do_corrupt(const std::string& fn);
    std::string read_file();
    bool try_read(const std::string& fn);

protected:
    static Core* _instance;
    Core();

public:
    bool bDebug = true;
    TestCategory kTest = TEST_DEFAULT;
    quint32 prepare_length = 0;
    quint8 prepare_fill = 0;
    std::string prepare_fn = "default.out";
    quint32 corrupt_length = 0;
    quint32 corrupt_count = 0;
    quint8 corrupt_byte = 0xFF;
    std::string read_fn = "default.json";
    std::vector<std::string> v;
};

#endif  // __CORE_H__
