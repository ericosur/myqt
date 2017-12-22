
#include "handleopt.h"

#include "getcover.h"
#include "tbhash.h"
#include "worker.h"
#include "core.h"

#include <QCoreApplication>
#include <QUrl>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "json.hpp"

using namespace std;

bool gDebug = false;

QString test_encode(const QString& str)
{
    return QUrl::toPercentEncoding(str);
}

QString test_decode(const QString& str)
{
    return QUrl::fromPercentEncoding(str.toLocal8Bit());
}

void oops(const QString& cmd)
{
    QRegularExpression re("(?<key>[A-Za-z][A-Za-z0-9_]*)\\s*=\\s*(?<val>[^/]+)");
    QRegularExpressionMatchIterator i = re.globalMatch(cmd);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString key = match.captured("key");
        QString val = match.captured("val");
        CHECK_IF_DEBUG( qDebug() << "match: " << key << "=" << test_decode(val) );
    }
}

int run_worker(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    Core::getInstance()->start();

    return app.exec();
}

void process_one_file(const QString& fn)
{
    QString tbfn;
    if (GetCover::isFileExisted(fn)) {
        cout << "file: " << fn.toStdString() << endl;
        if ( TbHash::getInstance()->getThumbnail(fn, tbfn) )  {
            cout << "save thumbnail to: " << tbfn.toStdString() << endl;
        } else {
            qWarning() << "getThumbnail() nok";
        }
    } else {
        qWarning() << "not exists:" << fn;
    }
}


void read_from_list(const QString& listfn)
{
#define DEFAULT_BUFFER_SIZE   (1024)

    FILE* ptr = fopen(listfn.toUtf8(), "r");
    if (ptr == NULL) {
        perror("fopen");
        return;
    }
    char line[DEFAULT_BUFFER_SIZE];
    int cnt = 0;
    while (!feof(ptr)) {
        char* p = fgets(line, DEFAULT_BUFFER_SIZE-1, ptr);
        if (p == NULL) {
            break;
        }
        QString fn(line);
        fn.chop(1);
        process_one_file(fn);
        cnt ++;
    }
    fclose(ptr);
    QString msg = QString("%1 records processed").arg(cnt);
    qDebug() << msg;
}

void read_from_json(const QString& listjson)
{
    try {
        std::ifstream infile(listjson.toUtf8().toStdString());
        nlohmann::json j;
        infile >> j;

        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
            nlohmann::json item = (*it);
            cout << item << endl;
        }

        qDebug() << "json file imported, and stop";
        exit(1);
    } catch (nlohmann::json::parse_error& e) {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
    }

}

void print_help()
{
    fprintf(stderr, "getcover built at %s %s\nUsing %s\n\n",
            __DATE__, __TIME__, GetCover::getTablibVersion().toUtf8().data());
    fprintf(stderr,
            "getcover [options] [audio media files]\n"
            "\t-h  help message\n"
            "\t-i  follow thumbnail media type (default:off)\n"
            "\t-t  turn off hash table (default:on)\n"
            "\t-n  Not output thumbnail file (default: on)\n"
            "\t-r  resize width and height of thumbnail (default:off)\n"
            "\t-v  verbose (default:%s)\n"
            "\t-j  specify list file in json format\n"
            "\t-f  specify list file\n"
            "\t-w  use worker\n"
            "\t-d  percent decode\n"
            "\t-e  percent encode\n",
            (gDebug ? "yes" : "no")
    );
}


void handleopt(int argc, char** argv)
{
    bool use_hashtable = true;
    QString listfn;
    QString listjson;

    if (argc == 1) {
        print_help();
        return;
    }

    while (1) {
        int cmd_opt = getopt(argc, argv, "d:e:f:hij:nrtvw");
        if (cmd_opt == -1) {    // all parsed
            //qDebug() << "cmd_opt == -1";
            break;
        }
        switch (cmd_opt) {
        case 'd':
            if (optarg) {
                QString str = optarg;
                qDebug() << "str:" << str << endl << test_decode(str);
                exit(EXIT_OK);
            }
            break;
        case 'e':
            if (optarg) {
                QString str = optarg;
                qDebug() << "str:" << str << endl << test_encode(str);
                exit(EXIT_OK);
            }
            break;
        case 'f':
            if (optarg) {
                listfn = optarg;
                CHECK_IF_DEBUG( qDebug() << "use list file:" << listfn );
            }
            break;
        case 'h':
            print_help();
            exit(EXIT_OK);
            break;
        case '?':
            print_help();
            exit(EXIT_INVALID_OPT);
            break;
        case 'i':
            GetCover::setFollowImageType(true);
            CHECK_IF_DEBUG( qDebug() << "will follow thumbnail image format..." );
            break;
        case 'j':
            if (optarg) {
                listjson = optarg;
                CHECK_IF_DEBUG( qDebug() << "use json file:" << listjson );
            }
            break;
        case 't':
            use_hashtable = false;
            qDebug() << "use thumbnail hash table?" << (use_hashtable?"yes":"no");
            break;
        case 'n':
            GetCover::setWriteTb(false);
            CHECK_IF_DEBUG( qDebug() << "will not write tb to disk..." );
            break;
        case 'r':
            GetCover::setResizeTb(true);
            CHECK_IF_DEBUG( qDebug() << "will resize tb width/height..." );
            break;
        case 'v':
            gDebug = !gDebug;
            break;
        case 'w':
            {
                int ret = run_worker(argc, argv);
                exit(ret);
            }
            break;
        default:
            break;
        }
    }

    // if still cli arguments available
    if (argc > optind) {
        //qDebug() << "optind:" << optind;
        for (int i = optind; i < argc; i++) {
            QString clifn = argv[i];
            process_one_file(clifn);
        }
    }

    if (use_hashtable) {
        TbHash::getInstance()->load();
    }
    if (listfn != "") {
        read_from_list(listfn);
    } else if (listjson != "") {
        read_from_json(listjson);
    }

    if (use_hashtable) {
        TbHash::getInstance()->save();
    }

}
