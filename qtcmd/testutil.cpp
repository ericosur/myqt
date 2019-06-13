#include "testutil.h"

ConfigVar gVars;

void print_help()
{
    printf("help message =====>\n\n"
        "-1 [string]             sha1sum of specified string\n"
        "-3 [string]             sha3sum of specified string\n"
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
            int cmd_opt = getopt(argc, argv, "1:3:5:ac:df:hk:m:p");
            if (cmd_opt == -1) {
                //qDebug() << "cmd_opt == -1";
                break;
            }
            switch (cmd_opt) {
            case 'h':   // help
                print_help();
                exit(2);
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
            case 'd':   // debug
                gVars.bDebug = !gVars.bDebug;
                configured = true;
                break;
            case 'f':   // read conf file
                if (optarg) {
                    gVars.kTest = TC_READCONFIG;
                    configured = true;
                    gVars.sConfig = optarg;
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
            case 'p':
                configured = true;
                gVars.kTest = TC_PROCESS;
                break;
            case '1':
                if (optarg) {
                    gVars.kTest = TC_SHA1SUMTEST;
                    configured = true;
                    gVars.sTeststring = optarg;
                }
                break;
            case '3':
                if (optarg) {
                    gVars.kTest = TC_SHA3SUMTEST;
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


QString get_one_string(int idx)
{
    QStringList sl;
    sl << "1234" << "apple" << "ball" << "cat" << "dog";

    return sl.at(idx % sl.size());
}

QString getHash(const QString& hashname, const QString& str)
{
    typedef QString (*Hasher)(const char*, int);

    QHash<QString, Hasher> hh = {
        {"md5sum", md5sum},
        {"sha1sum", sha1sum},
        {"sha3_256sum", sha3_256sum},
        {"keccak_256sum", keccak_256sum}
    };

    Hasher pf = hh.value(hashname, nullptr);
    if (pf != nullptr) {
        char *input = str.toUtf8().data();
        QString md = (*pf)(input, strlen(input));
        qDebug() << QString("%1(%2) => %3").arg(hashname).arg(str).arg(md);
        return md;
    } else {
        qDebug() << "invalid hashname:" << hashname;
    }

    return QString();
}

// echo -n "1234" | md5sum
QString get_md5sum(const QString& str)
{
    return getHash("md5sum", str);
}

// echo -n "1234" | sha1sum
QString get_sha1sum(const QString& str)
{
    return getHash("sha1sum", str);
}

QString get_sha3sum(const QString& str)
{
    getHash("sha3_256sum", str);
    getHash("keccak_256sum", str);
    return QString();
}

QString get_sha3sum2(const QString& str)
{
    return getHash("keccak_256sum", str);
}

void test_sha1hmac()
{
    QByteArray key = gVars.sKeystring.toUtf8();
    QByteArray str = gVars.sTeststring.toUtf8();
    qDebug() << QString("key:%1,str:%2 ==> %3").arg(gVars.sKeystring)
                    .arg(gVars.sTeststring)
                    .arg(hmacSha1(key, str));
}
