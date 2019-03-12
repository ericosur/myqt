#ifndef __TEST_TEST_H__
#define __TEST_TEST_H__

#include "../readjson.h"
#include "../fileutil.h"
#include <QDebug>

#define SHOWHEADER()    \
    qDebug() << Q_FUNC_INFO << "===>"

void test();
void testvm();

#endif  // __TEST_TEST_H__
