/// \file main.cpp
///

#include <QCoreApplication>
#include <QDebug>

#include "commontest.h"
#include "util.h"

#include "foo.h"
#include "testz.h"
#include "readi.h"

#include "devinfo.h"

// qtlib
#include "trypath.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    if ( handleOpt(argc, argv) ) {
        qDebug() << "debug mode:" << gVars.bDebug;
    }

    for (auto k : gVars.test_list) {
        switch (k) {
        case TEST_DEFAULT:
            run_default_tests();
            break;
        case TEST_DIRSEARCH:
            print_title("test: testdir...");
            testdir( getHomepath() );
            print_sep();
            testread();
            print_sep();
            break;
        case TEST_PERCENTENCODING:
            print_title("test: percent encoding...");
            qDebug() << toPercentEncoding(gVars.sTest);
            break;
        case TEST_LOCALTIME:
            print_title("test: test locale...");
            test_locale();
            print_title("test: test timezone");
            test_timezone();
            print_title("test: gtz");
            gtz();
            break;
        case TEST_RUNSCRIPT:
            print_title("test: test_runscript");
            test_runscript();
            break;
        case TEST_READCONF:
            print_title("test: read config");
            test_read_config();
            break;
        default:
            qWarning() << "should not be here!";
            break;
        }
    }

    return 0;
}
