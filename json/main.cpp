#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <stdio.h>

#include "trypath.h"
#include "readjson.h"
#include "util.h"

QStringList plist;

bool mySearchAndOpenFile(const QString& fn, QString& result)
{
    if (searchFileFromList(plist, fn, result)) {
        if (gDebug)
            qDebug() << "will open file from:" << result;
        ReadJson rj(result);
        rj.loadFile();
        return true;
    } else {
        qDebug() << "not found";
        return false;
    }
}

void queryWeather(const QString& city)
{
    QString key = "*";
    // QString key = "item.condition";
    // if (gSelectAll)
    //     key = "*";

    QString curlcmd = QString("/usr/bin/curl https://query.yahooapis.com/v1/public/yql "
                      "-d q=\x22select %1 from weather.forecast "
                      "where woeid in (select woeid from geo.places(1) where text='%2') and u='c'"
                      "\x22 -d format=json").arg(key).arg(city);
    if (gDebug)
        qDebug() << "queryWeather(): curlcmd: " << curlcmd;

    QProcess ps;
    ps.start(curlcmd);
    ps.waitForFinished(-1);

    QString stdout = ps.readAllStandardOutput();
    if (gDebug)
        qDebug() << stdout;
    writeStringToFile(stdout, DEFAULT_OUTPUT_FN);
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    handleOpt(argc, argv);

    plist << "./" << "../" << "/tmp/" << getHomepath();

    if (gFilename.isEmpty()) {
        qDebug() << "query weather of" << CITYNAME << " from internet =====>";
        queryWeather(CITYNAME);
        gFilename = DEFAULT_OUTPUT_FN;
    }

    ReadJson rj(gFilename);
    rj.loadFile();
    rj.test();

    return 0;

}
