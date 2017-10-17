#include "util.h"
#include "commontest.h"
#include "trypath.h"

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
    QString tmp = key;
    int cnt = 1;
    while (sl.contains(tmp)) {
        tmp = QString("%1 (%2)").arg(key).arg(cnt);
        cnt ++;
    }
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
    qDebug() << sl;
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
