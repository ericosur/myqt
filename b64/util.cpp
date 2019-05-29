#include "util.h"

ConfigVar gVars;

void print_help()
{
    printf("help message =====>\n\n"
        "-d                      toggle debug\n"
        "-e [test string]        percent encoding\n"
        "-f                      perform testdir\n"
        "-r                      perform runscript\n"
        "-t                      perform timezone tests\n"
        "-h                      help message\n\n");
}

void print_brief_help()
{
    printf("use -h to see help message\n\n");
}

bool handleOpt(int argc, char** argv)
{
    do {
        if (argc == 1) {
            print_brief_help();
            break;
        }

        while(1) {
            int cmd_opt = getopt(argc, argv, "cde:fhrt");
            if (cmd_opt == -1) {
                //qDebug() << "cmd_opt == -1";
                break;
            }
            switch (cmd_opt) {
            case 'h':   // help
                print_help();
                exit(2);
                break;
            case 'c':
                gVars.test_list << TEST_READCONF;
                break;
            case 'd':   // debug
                gVars.bDebug = !gVars.bDebug;
                break;
            case 'e':   // percent encoding string
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "test percent encoding:" << optarg );
                    gVars.sTest = optarg;
                    gVars.test_list << TEST_PERCENTENCODING;
                }
                break;
            case 'f':
                gVars.test_list << TEST_DIRSEARCH;
                break;
            case 'r':
                gVars.test_list << TEST_RUNSCRIPT;
                break;
            case 't':
                gVars.test_list << TEST_LOCALTIME;
                break;
            default:
                break;
            }
        }
    } while (false);

    if (gVars.test_list.empty()) {
        gVars.test_list << TEST_DEFAULT;
    }
    return true;
}

