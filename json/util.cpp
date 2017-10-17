#include "util.h"

// using stdc FILE* to write
bool writeStringToFile(const QString& str, const QString& fn)
{
    FILE* fp = fopen(fn.toUtf8().constData(), "w");
    if (fp == NULL) {
        qDebug() << "cannot write file:" << fn;
        return false;
    }
    fprintf(fp, "%s", str.toUtf8().constData());
    fclose(fp);
    CHECK_IF_DEBUG(qDebug() << "writeStringToFile(): write to" << fn);
    return true;
}

// using QFile to write
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn)
{
    QFile outFile(fn);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "fail to write file:" << fn;
        return false;
    }
    if ( outFile.write(arr) == -1 ) {
        return false;
    }
    return true;
}

void print_help()
{
    printf("help message =====>\n\n"
        "-a              query all elements\n"
        "-c              using specified config\n"
        "-d              turn on all debug message\n"
        "-f [filename]   load from file\n"
        "-g [filename]   dump config to file\n"
        "-o [filename]   output to file\n"
        "-q              query via internet\n"
        "-h              help message\n\n");
}

void print_brief_help()
{
    printf("use -h to see help message\n\n");
}

bool handleOpt(int argc, char** argv)
{
    bool configured = false;
    UtilVars* _vars = UtilVars::getInstance();
    do {
        if (argc == 1) {
            print_brief_help();
            break;
        }

        while(1) {
            int cmd_opt = getopt(argc, argv, "ac:df:g:ho:q");
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
                _vars->bSelectAll = true;
                break;
            case 'c':   // config file
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "config file:" << optarg );
                    _vars->sConfig = optarg;
                    configured = true;
                }
                break;
            case 'd':   // debug
                //qDebug() << "c:" << optarg;
                configured = true;
                _vars->bDebug = true;
                break;
            case 'f':   // load from file
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "assign json file:" << optarg );
                    _vars->sFilename = optarg;
                    configured = true;
                }
                break;
            case 'g':   // output to file
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "config dump to:" << optarg );
                    _vars->sOutconfig = optarg;
                    configured = true;
                }
                break;
            case 'o':   // output to file
                if (optarg) {
                    CHECK_IF_DEBUG( qDebug() << "output file to:" << optarg );
                    _vars->sOutfile = optarg;
                    configured = true;
                }
                break;
            case 'q':   // query via internet
                _vars->bQueryViaInternet = true;
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

