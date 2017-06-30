#include "util.h"

bool gSelectAll = false;
bool gDebug = false;

void writeStringToFile(const QString& str, const QString& fn)
{
    FILE* fp = fopen(fn.toUtf8().constData(), "w");
    if (fp == NULL) {
        qDebug() << "cannot write file";
        return;
    }
    fprintf(fp, "%s", str.toUtf8().constData());
    fclose(fp);
    if (gDebug)
        qDebug() << "writeStringToFile(): write to" << fn;
}

void print_help()
{
    printf("help message =====>\n\n"
        "-a    query all elements\n"
        "-d    turn on all debug message\n"
        "-h    help message\n\n");
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
            int cmd_opt = getopt(argc, argv, "adh");
            if (cmd_opt == -1) {
                //qDebug() << "cmd_opt == -1";
                break;
            }
            switch (cmd_opt) {
            case 'h':   // help
                print_help();
                exit(2);
                break;
            case 'a':   // all elements
                configured = true;
                gSelectAll = true;
                break;
            case 'd':   // debug
                //qDebug() << "c:" << optarg;
                configured = true;
                gDebug = true;
                break;
            default:
                exit(0);
                break;
            }
        }
    } while (false);

    return configured;
}
