#include "testutil.h"

ConfigVar gVars;

void print_help()
{
    printf("help message =====>\n\n"
        "-1 [string]             sha1sum of specified string\n"
        "-5 [string]             md5sum of specified string\n"
        "-k [string]             specify key string\n"
        "-d                      toggle debug\n"
        "-c [number]             generate SHA1-HMAC with specified count\n"
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
            int cmd_opt = getopt(argc, argv, "1:5:c:dhk:m:");
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
            case 'a':
                gVars.kTest = TC_ARRAYTEST;
                configured = true;
                break;
            case 'c':   // percent encoding string
                if (optarg) {
                    //CHECK_IF_DEBUG( qDebug() << "test percent encoding:" << optarg );
                    QString cnt = optarg;
                    gVars.iCount = cnt.toInt();
                    gVars.kTest = TC_MD5LISTTEST;
                    configured = true;
                }
                break;
            case 'k':
                if (optarg) {
                    gVars.sKeystring = optarg;
                }
            case 'm':
                if (optarg) {
                    gVars.kTest = TC_HMACTEST;
                    gVars.sTeststring = optarg;
                }
                break;
            case '1':
                if (optarg) {
                    gVars.kTest = TC_SHA1SUMTEST;
                    configured = true;
                    gVars.sTeststring = optarg;
                }
                break;
            case '5':
                if (optarg) {
                    gVars.kTest = TC_MD5SUMTEST;
                    configured = true;
                    gVars.sTeststring = optarg;
                }
                break;
            default:
                exit(0);
                break;
            }
        }
    } while (false);

    return configured;
}

