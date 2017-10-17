/// \file main.cpp
///

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QDebug>

#include "commontest.h"
#include "util.h"

#include "foo.h"
#include "testz.h"
#include "readi.h"

#include "devinfo.h"
#include "testmm.h"

// qtlib
#include "trypath.h"

void gtz();

void testdir(const QString& _home)
{
    QDir dir;
    if ( !try_path(_home, dir) ) {
        qWarning() << "no proper dir...";
        return;
    }

    Foo foo;
    QStringList filter;

    foo.clear();
    qDebug() << "will output search result to:" << foo.getInifn();
    filter << "*.mp3" << "*.m4a" << "*.ape" << "*.wav";
    int cnt = 0;

    foreach (QString file, dir.entryList(filter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullpath = _info.filePath();
        QString _encoded = QFile::encodeName(_fullpath);
        QUrl _url = QUrl::fromLocalFile(_fullpath);

        qDebug() << "_fullpath:" << _fullpath;
        qDebug() << "encodename:" << _encoded;
        qDebug() << "url:" << _url;

        if (QFile::exists(_fullpath)) {
            foo.saveString(cnt, _fullpath);
        } else {
            qDebug() << "_fullpath nok:" << _fullpath;
        }

        if (QFile::exists(_encoded)) {
            foo.saveEncoded(cnt, _encoded);
        } else {
            qDebug() << "check encode fail:" << _encoded;
        }

        foo.saveUrl(cnt, _url);

        cnt ++;
    }

    if (cnt == 0) {
        qWarning() << "no files found...";
    }
}

QUrl readUrl(int idx)
{
    qDebug() << Q_FUNC_INFO;
    Foo bar;
    QUrl url;
    if ( bar.readUrl(idx, url) ) {
        qDebug() << url;
        return url;
    }
    return QUrl();
}

void testread()
{
    qDebug() << Q_FUNC_INFO;
    Foo bar;
    QUrl url;
    int urlcount = bar.getUrlCount();

    for (int i=0; i<urlcount; i++) {
        if ( bar.readUrl(i, url) ) {
            qDebug() << url;
            bool ret = QFile::exists(url.toLocalFile());
            qDebug() << "exist?" /* << _f.fileName() << endl */
                 << ret;
        }
    }
}

void test_info()
{
    DeviceScreen ds;
    qDebug() << ds.getInfostring();
}


void run_default_tests()
{
    // default tests
    print_title("test: QMultiMap");
    testmm();
    //print_sep();

    print_title("test: no_conflict_name");
    no_conflict_name();

    print_title("test: get home path");
    qDebug() << "home path:" << getHomepath();

    print_title("test: arg...");
    test_arg_format();

    print_title("test: doSanity");
    QString s = "I don't know!";
    qDebug() << "test:" << doSanity(s);

    print_title("test: deviceinfo...");
    test_info();

    print_title("test: test__pe");
    test__pe();
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    if ( handleOpt(argc, argv) ) {
        qDebug() << "debug mode:" << gVars.bDebug;
    }

    switch (gVars.kTest) {
    case TEST_DEFAULT:
        run_default_tests();
        break;
    case TEST_DIRSEARCH:
        print_title("test: testdir...");
        testdir( getHomepath() );
        print_sep();
        testread();
        print_sep();
        test_read_ini();
        print_sep();
        return 0;
    case TEST_PERCENTENCODING:
        print_title("test percent encoding...");
        qDebug() << toPercentEncoding(gVars.sTest);
        return 0;
    case TEST_LOCALTIME:
        print_title("test: test locale...");
        test_locale();
        print_title("test: test timezone");
        test_timezone();
        print_title("test: gtz");
        gtz();
        return 0;
    case TEST_RUNSCRIPT:
        print_title("test: test_runscript");
        test_runscript();
        return 0;
    default:
        qWarning() << "should not be here!";
        break;
    }

    return 0;
}
