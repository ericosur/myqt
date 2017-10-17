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
    bool configured = false;

    do {
        if (argc == 1) {
            print_brief_help();
            break;
        }

        while(1) {
            int cmd_opt = getopt(argc, argv, "de:fhrt");
            if (cmd_opt == -1) {
                //qDebug() << "cmd_opt == -1";
                break;
            }
            switch (cmd_opt) {
            case 'h':   // help
                print_help();
                exit(2);
                break;
            case 'd':   // debug
                gVars.bDebug = !gVars.bDebug;
                configured = true;
                break;
            case 'e':   // percent encoding string
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "test percent encoding:" << optarg );
                    gVars.sTest = optarg;
                    gVars.kTest = TEST_PERCENTENCODING;
                    configured = true;
                }
                break;
            case 'f':
                gVars.kTest = TEST_DIRSEARCH;
                configured = true;
                break;
            case 'r':
                gVars.kTest = TEST_RUNSCRIPT;
                configured = true;
                break;
            case 't':
                gVars.kTest = TEST_LOCALTIME;
                configured = true;
                break;
            default:
                exit(0);
                break;
            }
        }
    } while (false);

    return configured;
}

