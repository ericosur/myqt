#ifndef __UTIL_H__
#define __UTIL_H__

#include <QString>
#include <QDebug>

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

#define EXIT_REASON_ERROR   (-1)
#define EXIT_REASON_HELP    (-2)

bool handleOpt(int argc, char** argv);
void print_help();

enum TestCategory {
    TEST_DEFAULT = 0,
};


#endif  // __UTIL_H__
