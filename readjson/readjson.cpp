/// file: readjson.cpp

// simple class to use QJsonDocument and QJsonObject

#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QDebug>

#include "readjson.h"

ReadJson::ReadJson()
{
}

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
    mJsonString = QString(saveData);
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
}

#if 0
void ReadJson::testString()
{
    qDebug() << "test get string from following path....";
    QStringList sl;
    sl << "default.right.name"
        << "default.right.url"
        << "default.left.name"
        << "default.left.url";


    QList<QString>::const_iterator i;
    for (i = sl.constBegin(); i != sl.constEnd(); ++i)
        qDebug() << *i << ":" << getLeafString(*i);
}

void ReadJson::testArray()
{
    qDebug() << "read array from json...";
    QJsonValue v = getLeafValue("items");
    if (v.isArray()) {
        QJsonArray _arr = v.toArray();

        for (int ii=0; ii<_arr.size(); ++ii) {
            //qDebug() << _arr[ii] ;
            if (_arr[ii].isObject()) {
                dumpOneArrayElem(_arr[ii].toObject());
            } else {
                qWarning() << "not an object!";
            }

        }
    } else {

    }
}

void ReadJson::dumpOneArrayElem(const QJsonObject& o)
{
    qDebug() << "dumpOneArrayElem:" << getString(o, "name")
        << getString(o, "url");
}
#endif

QString ReadJson::getString(const QJsonObject& o, const QString& key)
{
    if (o[key].isString()) {
        return o[key].toString();
    } else {
        return QString();
    }
}

QJsonArray ReadJson::getLeafArray(const QString& path)
{
    QJsonValue v = getLeafValue(path);
    if (v.isArray()) {
        return v.toArray();
    } else {
        qWarning() << "specified path is not an array!";
    }
    return QJsonArray();
}

QJsonObject ReadJson::getLeafArrayAt(const QString& path, int idx)
{
    qDebug() << "read array from json, assign at:" << idx << "from:" << path;

    QJsonArray _arr = getLeafArray(path);
    if (_arr.isEmpty()) {
        qDebug() << __func__ << "array is empty, exit...";
        return QJsonObject();
    }

    if (idx >= 0 && idx < _arr.size()) {
        if (_arr[idx].isObject()) {
            return _arr[idx].toObject();
        } else {
            qWarning() << "not an object!";
            return QJsonObject();
        }
    } else {
        qWarning() << "out of bound!";
    }

    return QJsonObject();
}

void ReadJson::checkValueType(const QJsonValue& v)
{
    QString typestr;
    switch (v.type()) {
    case QJsonValue::Null:
        typestr = "null";
        break;
    case QJsonValue::Bool:
        typestr = "bool";
        break;
    case QJsonValue::Double:
        typestr = "double";
        break;
    case QJsonValue::String:
        typestr = "string";
        break;
    case QJsonValue::Array:
        typestr = "array";
        break;
    case QJsonValue::Object:
        typestr = "object";
        break;
    case QJsonValue::Undefined:
        typestr = "undefined";
        break;
    }
    qDebug() << v << "is" << typestr;
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
            if (_obj[name].isString()) {
                result = _obj[name].toString();
            } else {
                checkValueType(_obj[name]);
                qWarning() << __func__ << "specified path is not a string:" << path;
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

    if (json[lhs].isObject()) {
        return json[lhs].toObject();
    } else {
        return QJsonObject();
    }

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

QMap<QString, QString> ReadJson::getMapFromList(const QStringList sl)
{
    QMap<QString, QString> map;

    QList<QString>::const_iterator i;
    for (i = sl.constBegin(); i != sl.constEnd(); ++i) {
        //qDebug() << *i << ":" << getLeafString(*i);
        map.insert(*i, getLeafString(*i));
    }
    return map;
}

void ReadJson::dumpJsonObj(const QJsonObject& obj)
{
    QJsonObject::const_iterator i;
    for (i = obj.constBegin(); i != obj.constEnd(); ++i) {
        qDebug() << *i;
    }
}