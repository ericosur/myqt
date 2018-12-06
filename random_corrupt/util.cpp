#include "util.h"
#include "core.h"


void print_help()
{
    printf("help message =====>\n\n"
        "-h                      help message\n\n"
        "-d                      toggle debug\n"
    );
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
            int cmd_opt = getopt(argc, argv, "dh");
            if (cmd_opt == -1) {
                //qDebug() << "cmd_opt == -1";
                break;
            }
            switch (cmd_opt) {
            case 'h':   // help
                print_help();
                exit(EXIT_REASON_HELP);
                break;
            case 'd':   // debug
                {
                    Core* pcore = Core::getInstance();
                    pcore->bDebug = !pcore->bDebug;
                }
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
