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

void dumpForecastArrayElem(const QJsonObject& o)
{
#define getString(obj, key) \
    key << ":" << obj[key].toString()

    qDebug() << getString(o, "code")
        << getString(o, "date")
        << getString(o, "day")
        << getString(o, "high")
        << getString(o, "low")
        << getString(o, "text");
}

void testArray(const QJsonArray& arr)
{
    qDebug() << Q_FUNC_INFO;

#define NEXT_FEW_DAYS       (4)

    qDebug() << "forecast for next few days...";

    for (int ii=0; ii<NEXT_FEW_DAYS; ++ii) {
        if (arr[ii].isObject()) {
            dumpForecastArrayElem(arr[ii].toObject());
        } else {
            qWarning() << "not an object!";
        }
    }

}

void testString(ReadJson& rj)
{
    qDebug() << Q_FUNC_INFO;
    QStringList sl;
    sl << "query.results.channel.description"
        << "query.results.channel.astronomy.sunrise"
        << "query.results.channel.astronomy.sunset"
        << "query.results.channel.atmosphere.humidity"
        << "query.results.channel.atmosphere.pressure"
        << "query.results.channel.item.condition.code"
        << "query.results.channel.item.condition.date"
        << "query.results.channel.item.condition.temp"
        << "query.results.channel.item.condition.text"
        << "query.results.channel.language"
        << "query.results.channel.location.city"
        << "query.results.channel.location.country"
        << "query.results.channel.location.region"
        << "query.results.channel.units.distance"
        << "query.results.channel.units.pressure"
        << "query.results.channel.units.speed"
        << "query.results.channel.units.temperature"
        ;

    QMap<QString, QString> map = rj.getMapFromList(sl);
    for (int i = 0; i < sl.size(); i++) {
        qDebug() << sl.at(i) << ":" << map.value(sl.at(i));
    }

    qDebug() << endl << "test dumpJsonObj ===> ";
    QJsonObject obj = rj.getLeafObject("query.results.channel.wind");
    rj.dumpJsonObj(obj);

}

void processJson(const QString& fn)
{
    ReadJson rj(fn);
    if ( !rj.loadFile() ) {
        qWarning() << "load json file failed, exit...";
        return;
    }

    rj.test();
    //testString(rj);
    //testArray( rj.getLeafArray("query.results.channel.item.forecast") );
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

    processJson(gFilename);

    return 0;

}
