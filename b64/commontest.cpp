#include "util.h"
#include "commontest.h"
#include "trypath.h"

#include <QTextCodec>
#include <QList>
#include <QStringList>

#define MAXLINELEN  (70)
#define REPEAT      (60)

void repeat_sep(int n)
{
    if (n>0 && n<=MAXLINELEN) {
        for (int i = 0; i < n; i ++) {
            fputc('=', stdout);
        }
    }
}

void print_title(const char* title)
{
    size_t title_len = strlen(title);

    if (title_len > MAXLINELEN) {
        printf("%s\n", title);
        return;
    }

    size_t sep_len1 = (MAXLINELEN - title_len) / 2;
    size_t sep_len2 = MAXLINELEN - title_len - sep_len1;
    repeat_sep(sep_len1);
    printf("%s", title);
    repeat_sep(sep_len2);
    printf("\n");
}

void print_sep()
{
    repeat_sep(MAXLINELEN);
    fputc('\n', stdout);
}

QString check_name(const QStringList& sl, const QString& key)
{
    Q_UNUSED(sl);
    Q_UNUSED(key);


    QString tmp = key;
    QStringList post;

    post << QChar(9) << QChar(10) << QChar(11) << QChar(12) << QChar(13) << QChar(32);
    //qDebug() << post;
    static int cnt = 0;
    if (cnt < post.size()) {
        qDebug() << cnt << "," << post.at(cnt);
        tmp = tmp + post.at(cnt);
        cnt ++;
    } else {
        cnt = 0;
    }
    // while (sl.contains(tmp)) {
    //     tmp = QString("%1%2").arg(key).arg(post.at(cnt));
    //     if (cnt < post.size())
    //         cnt ++;
    //     else
    //         cnt = 0;
    // }
    return tmp;
}

// if name is existed at string list, will append (1) (2) (...)
// at the tail of string
//
// for example input "apple" three times
// first: "apple"
// 2nd: "apple (1)"
// 3rd: "apple (2)"
//
void no_conflict_name()
{
    QStringList sl;
    QString ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);
    ret = check_name(sl, "apple");
    sl.append(ret);

    qDebug() << sl;
}

// 0x2764, 0xfe0f
// b'\xe2\x9d\xa4' b'\xef\xb8\x8f'
// 0x1f1e7, 0x1f1f4
// b'\xf0\x9f\x87\xa7'  b'\xf0\x9f\x87\xb4'
// 0x1f64b, 0x200d, 0x2640, 0xfe0f
// b'\xf0\x9f\x99\x8b' b'\xe2\x80\x8d' b'\xe2\x99\x80' b'\xef\xb8\x8f'
// 0x1f3c8, 0x1f603
// b'\xf0\x9f\x8f\x88'  b'\xf0\x9f\x98\x83'
//
// "\u2764\ufe0f",
// "\U0001f1e7\U0001f1f4"
// "\U0001f64b\u200d\u2640\ufe0f"
// "\U0001f3c8\U0001f603"
//
void unicode_char()
{
    QStringList sl = {
        "\u2764\ufe0f",
        "\U0001f1e7\U0001f1f4",
        "\U0001f64b\u200d\u2640\ufe0f",
        "\U0001f3c8\U0001f603"
    };
    for (QString ss: sl) {
        qDebug() << ss;
    }

}

/// input: _home
/// output: _dir
///
bool try_path(const QString& _home, QDir& _dir)
{
#ifdef USE_TARGET
    QString dirpath = "/data";
#else
    QString dirpath = QString("%1/Dropbox/Music").arg(_home);
    //dirpath = QDir::fromNativeSeparators(dirpath);
#endif
    QDir dir( dirpath );
    if ( dir.exists() ) {
        _dir = dir;
        return true;
    }
    // 2nd try
    dirpath = QString("%1/Music").arg(_home);
    dir.setPath(dirpath);
    if ( dir.exists() ) {
        _dir = dir;
        return true;
    }
    return false;
}

void test_arg_format()
{
    const double pi = 3.14159265358979323846264338327950;
    printf("printf: pi: %lf\n", pi);
    qDebug() << "pi:" << pi << endl
        << "arg/f/4:" << QString("<%1>").arg(pi, 0, 'f', 4);
}

QString toPercentEncoding(const QString& str)
{
    return QUrl::toPercentEncoding(str, ",");
}


QString doSanity(const QString& str)
{
    QString res = str;
    res.replace("'", "''");
    return res;
}

void test__pe()
{
    QString s = "03-Yes, My Dream";
    QString p = toPercentEncoding(s);
    qDebug() << p;
    QString result = QString("title=%1/message=%2").arg(p).arg("#####");
    qDebug() << result;
}

void test_runscript()
{
    QString script_name = "mytestscript";
    QString result;
    QStringList plist;
    QString homebin = getHomepath() + "/bin";
    // will search script from this path list
    plist << "./" << "../" << homebin;

    if (searchFileFromList(plist, script_name, result)) {
        qDebug() << "run script from:" << result;
    } else {
        qDebug() << "script not found, run it directly...";
        result = script_name;
    }

    QProcess process;
    process.start(result);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    qDebug() << "stdout: " << stdout;
    qDebug() << "stderr: " << stderr;

    process.close();
}
