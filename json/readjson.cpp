/// file: readjson.cpp

// simple class to use QJsonDocument and QJsonObject

#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QDebug>

#include "readjson.h"

ReadJson::ReadJson(const QString &f) :
    mFile(f)
{

}

bool ReadJson::loadFile()
{
    if (mFile == "") {
        qWarning("file name not specified");
        return false;
    } else {
        return loadFile(mFile);
    }
}

bool ReadJson::loadFile(const QString &filename)
{
    QFile f(filename);

    if (!f.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    qDebug() << "read json file from:" << filename;
    QByteArray saveData = f.readAll();
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData) );
    mJson = loadDoc.object();
    read(mJson);

    return true;
}

QString F2C(double f)
{
    double c = (f - 32.0) * 5.0 / 9.0;
    return QString::number(c);
}

void ReadJson::read(const QJsonObject &json)
{
    Q_UNUSED(json);
#if 0
    QJsonObject item = (((json["query"].toObject())["results"].toObject())["channel"].toObject())["item"].toObject();
    //qDebug() << item;
    QString f_string = (item["condition"].toObject())["temp"].toString();
    QString result = QString("%1°C").arg(F2C(f_string.toDouble()));
    qDebug() << "temperature:" << result;
    qDebug() << "weather:" << (item["condition"].toObject())["text"].toString();
#endif

}

void ReadJson::testString()
{
    qDebug() << "test get string from following path....";
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

    QList<QString>::const_iterator i;
    for (i = sl.constBegin(); i != sl.constEnd(); ++i)
        qDebug() << *i << ":" << getLeafString(*i);
}

QString ReadJson::getString(const QJsonObject& o, const QString& key)
{
    if (o[key].isString()) {
        return o[key].toString();
    } else {
        return QString();
    }
}

void ReadJson::dumpForecastArrayElem(const QJsonObject& o)
{
    qDebug() << getString(o, "code")
        << getString(o, "date")
        << getString(o, "day")
        << getString(o, "high")
        << getString(o, "low")
        << getString(o, "text");
}

void ReadJson::testArray()
{
#define NEXT_FEW_DAYS       (4)

    qDebug() << "forecast for next few days...";
    QJsonValue v = getLeafValue("query.results.channel.item.forecast");
    if (v.isArray()) {
        QJsonArray _arr = v.toArray();

        for (int ii=0; ii<NEXT_FEW_DAYS; ++ii) {
            //qDebug() << _arr[ii] ;
            dumpForecastArrayElem(_arr[ii].toObject());
        }
    }

}

void ReadJson::test()
{
    testString();

    //qDebug() << getLeafObject("query.results.channel.item.condition");
    //
    testArray();
}

void ReadJson::checkValueType(const QJsonValue& v)
{
    switch (v.type()) {
    case QJsonValue::Null:
        qDebug() << "is null";
        break;
    case QJsonValue::Bool:
        qDebug() << "is bool";
        break;
    case QJsonValue::Double:
        qDebug() << "is double";
        break;
    case QJsonValue::String:
        qDebug() << "is string";
        break;
    case QJsonValue::Array:
        qDebug() << "is array";
        break;
    case QJsonValue::Object:
        qDebug() << "is object";
        break;
    case QJsonValue::Undefined:
        qDebug() << "is undefined";
        break;
    }
}

QJsonValue ReadJson::getLeafValue(const QString& path)
{
    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject _next;
    QJsonValue result;

    while (true) {
        name = rhs;
         _next = fetchOneLevel(_obj, name, rhs);

         if (_next.isEmpty()) {
            //qDebug() << name << ":" << _obj[name].toString();
            result = _obj[name];
            break;
         } else {
            _obj = _next;
         }
    }

    return result;
}

QJsonObject ReadJson::getLeafObject(const QString& path)
{
    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject _next;
    QJsonObject result;

    while (true) {
        name = rhs;
         _next = fetchOneLevel(_obj, name, rhs);

         if (_next.isEmpty()) {
            //qDebug() << name << ":" << _obj[name].toString();
            QJsonValue _val = _obj[name];
            if (_val.isObject()) {
                result = _val.toObject();
            }
            break;
         } else {
            _obj = _next;
         }
    }

    return result;
}

QString ReadJson::getLeafString(const QString& path)
{
    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject _next;
    QString result;

    while (true) {
        name = rhs;
         _next = fetchOneLevel(_obj, name, rhs);

         if (_next.isEmpty()) {
            //qDebug() << name << ":" << _obj[name].toString();
            if (_obj[name].type() == QJsonValue::String) {
                result = _obj[name].toString();
            } else {
                qWarning() << "specified path is not a string!";
            }
            break;
         } else {
            _obj = _next;
         }
    }

    return result;
}

QJsonObject ReadJson::fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs)
{
    QString lhs = getLhs(input);
    rhs = getRhs(input);
    //qDebug() << "input:" << input;
    //     << "lhs:" << lhs << endl
    //     << "rhs:" << rhs;

    QJsonObject::const_iterator itr = json.find(lhs);
    if (itr == json.end()) {
        //qDebug() << "object not found:" << lhs;
        rhs = "";
        return QJsonObject();
    }

    return json[lhs].toObject();
}

// input: query.results.channel.description
// return: query, "" if no dot
QString ReadJson::getLhs(const QString& input)
{
    QString result;
    int idx = input.indexOf(".");
    if (idx != -1) {
        result = input.left(idx);
    }
    return result;
}
QString ReadJson::getRhs(const QString& input)
{
    QString result;
    int idx = input.indexOf(".");
    if (idx != -1) {
        result = input.right(input.length() - idx - 1);
    }
    return result;
}
