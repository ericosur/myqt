/// file: readjson.cpp

// simple class to use QJsonDocument and QJsonObject

#include "readjson.h"
#include <QPair>
#include <QStack>

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

bool ReadJson::readFileToByteArray(QByteArray& arr, const QString& fn)
{
    QFile inFile(fn);
    if (!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "fail to read file:" << fn;
        return false;
    }
    arr = inFile.readAll();
    return true;
}

bool ReadJson::loadFile(const QString &filename)
{
    //qDebug() << "read json file from:" << filename;
    QByteArray saveData;
    if (!readFileToByteArray(saveData, filename)) {
        return false;
    }
    mJsonString = QString(saveData);
    //qDebug() << "mJsonString:" << mJsonString;
    QJsonParseError err;
    mJdoc = QJsonDocument::fromJson(saveData, &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "json parse err:" << err.errorString();
        return false;
    }

    if (mJdoc.isNull()) {
        qDebug() << "loaded json is null";
    }
    if (mJdoc.isEmpty()) {
        qDebug() << "loaded json is empty";
    }
    mJson = mJdoc.object();

    return true;
}

bool ReadJson::saveFile(const QString& filename)
{
    return saveFile(filename, mJson);
}

bool ReadJson::saveFile(const QString& filename, const QJsonObject& jsonobj)
{
    QJsonDocument docjson(jsonobj);
    QFile JFile(filename);
    JFile.open(QIODevice::WriteOnly);
    JFile.write(docjson.toJson());
    return true;
}

QString F2C(double f)
{
    double c = (f - 32.0) * 5.0 / 9.0;
    return QString::number(c);
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
    default:
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
    QJsonValue result;

    while (true) {
        name = rhs;
         QJsonObject _next = fetchOneLevel(_obj, name, rhs);

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

QJsonObject ReadJson::buildjsonpath(const QString& path)
{
    QStack<QString> _stack;
    QString _p = path;

    while (!_p.isEmpty()) {
        QString lhs = getLhs(_p);
        QString rhs = getRhs(_p);
        qDebug() << "lhs:" << lhs << "," << "rhs:" << rhs;
        if (!lhs.isEmpty()) {
            //qDebug() << "build by LHS" << lhs;
            _stack.push(lhs);
        }
        if (rhs.isEmpty()) {
            //qDebug() << "build by _p" << _p;
            _stack.push(_p);
            break;
        }
        _p = rhs;
    }
    //qDebug() << "stack:" << _stack;

    QJsonObject j;
    QString prevkey;
    while (!_stack.isEmpty()) {
        QString top = _stack.pop();

        //qDebug() << "top:" << top;
        if (prevkey == "") {
            j[top] = top;
            //qDebug() << "j[top]:" << j[top];
        } else {
            QJsonObject _tmp;
            _tmp.insert(top, j);
            //qDebug() << "j[prevkey]" << j[prevkey];
            //qDebug() << "_tmp:" << _tmp << ", prevkey" << prevkey;
            j = _tmp;
        }
        prevkey = top;
        //qDebug() << "j:" << j;
    }

    return j;
}

QJsonObject ReadJson::setLeafValue(const QString& path, const QJsonValue& value)
{
    // peek before jumping
    QJsonValue _val = getLeafValue(path);
    if (_val.isNull()) {
        qDebug() << Q_FUNC_INFO << "value at path not existed:" << path << "will build it";
        QJsonObject _new = buildjsonpath(path);
    }

    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject _next;
    QString rootkey;

    typedef QPair<QString, QJsonObject> MyPair;
    QStack<MyPair> _stack;

    //qDebug() << Q_FUNC_INFO ;
    MyPair p;
    p.first = ".";
    p.second = _obj;
    _stack.push(p);

    while (true) {
        name = rhs;
         _next = fetchOneLevel(_obj, name, rootkey, rhs);
         //qDebug() << "fetchOneLevel: name:" << name << "rootkey:" << rootkey << "rhs:" << rhs;
         if (_next.isEmpty()) {
            // it is leaf
            //qDebug() << name << ":" << _obj[name].toString();
            _obj[name] = value;
            p = _stack.pop();    // last pair at top of stack
            MyPair q;   // new pair
            q.first = p.first;
            q.second = _obj;
            _stack.push(q);
            break;
         } else {
            // still something to go down
            _obj = _next;
            p.first = rootkey;
            p.second = _obj;
            _stack.push(p);
         }
    }

    //qDebug() << Q_FUNC_INFO << "stack size:" << _stack.size();
    QJsonObject rootobj;
    QJsonObject prevobj;
    for (size_t i=0; !_stack.isEmpty(); i++) {
        QJsonObject _tmp;
        p = _stack.pop();
        if (prevobj.isEmpty()) {
            if (p.first == ".") {
                _tmp = p.second;
            } else {
                _tmp.insert(p.first, p.second);
            }
            prevobj = _tmp;
            rootkey = p.first;
        } else {
            _tmp = p.second;
            if (p.first == ".") {
                // qDebug() << "p.first is dot... _tmp.insert(rootkey, prevobj);";
                // qDebug() << "          rootkey:" << rootkey;
                // qDebug() << "          prevobj:" << prevobj;
                //_tmp.insert(rootkey, prevobj);
                _tmp[rootkey] = prevobj[rootkey];
            } else {
                // qDebug() << "===> _tmp.insert(p.first, prevobj);";
                _tmp.insert(p.first, prevobj);
            }
            prevobj = _tmp;
            rootkey = p.first;
        }
        rootobj = _tmp;
    }

    mJson = rootobj;

    return mJson;
}

QJsonObject ReadJson::setLeafInt(const QString& path, int value)
{
    return setLeafValue(path, value);
}

QJsonObject ReadJson::setLeafArray(const QString& path, const QJsonArray& array)
{
    return setLeafValue(path, array);
}

QJsonObject ReadJson::setLeafArray(const QString& path, const QStringList& slist)
{
    return setLeafValue(path, QJsonArray::fromStringList(slist));
}

QJsonObject ReadJson::getLeafObject(const QString& path)
{
    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject result;

    while (true) {
        name = rhs;
        QJsonObject _next = fetchOneLevel(_obj, name, rhs);

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

QJsonObject ReadJson::getLeafObject(const QString& path, QString& lastname)
{
    QString name = path;
    QString rhs = name;
    QJsonObject _obj = mJson;
    QJsonObject result;

    while (true) {
        name = rhs;
         QJsonObject _next = fetchOneLevel(_obj, name, rhs);

         if (_next.isEmpty()) {
            //qDebug() << name << ":" << _obj[name].toString();
            lastname = name;
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

// it is an internal function
QJsonObject ReadJson::fetchdownlevel(const QJsonObject &json, const QString& lhs, QString& rhs)
{
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

QJsonObject ReadJson::fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs)
{
    rhs = getRhs(input);
    QString lhs = getLhs(input);
    //qDebug() << "input:" << input;
    //     << "lhs:" << lhs << endl
    //     << "rhs:" << rhs;
    return fetchdownlevel(json, lhs, rhs);
}

QJsonObject ReadJson::fetchOneLevel(const QJsonObject &json, const QString& input, QString& rootkey, QString& rhs)
{
    rhs = getRhs(input);
    rootkey = getLhs(input);
    return fetchdownlevel(json, rootkey, rhs);
}

// input: query.results.channel.description
// return: query, "" if no dot
QString ReadJson::getLhs(const QString& input)
{
    QString result;
    int idx = input.indexOf(".");
    if (idx != -1) {
        result = input.left(idx);
    } else {
        result = "";
    }
    return result;
}
QString ReadJson::getRhs(const QString& input)
{
    QString result;
    int idx = input.indexOf(".");
    if (idx != -1) {
        result = input.right(input.length() - idx - 1);
    } else {
        result = "";
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

void ReadJson::dumpJsonObjToDebug(const QJsonObject& obj)
{
    qDebug() << dumpJsonObjToString(obj);
}

QString ReadJson::dumpJsonObjToString(const QJsonObject& obj)
{
    QJsonObject::const_iterator i;
    QString _outstring;
    for (i = obj.constBegin(); i != obj.constEnd(); ++i) {
        _outstring.append((*i).toString());
    }
    return _outstring;
}

void ReadJson::dump()
{
    //qDebug() << Q_FUNC_INFO;
    dump(mJson);
}

void ReadJson::dump(const QJsonObject &json)
{
    qDebug() << Q_FUNC_INFO;
    if (json.isEmpty()) {
        qDebug() << "obj is empty";
        return;
    }

    dumpVariantMap(json.toVariantMap());
}

void ReadJson::dumpVariantList(const QVariantList& lst)
{
    QList<QVariant>::const_iterator i;
    for (i = lst.constBegin(); i != lst.constEnd(); ++i) {
        if (i->type() == QVariant::Map) {
            qDebug() << "  ::map ==>";
            dumpVariantMap(i->toMap());
        } else {
            qDebug() << *i << endl;
        }
    }
}

void ReadJson::dumpVariantMap(const QVariantMap& map)
{
    for (int i = 0; i < map.size(); ++ i) {
        QVariant _k = map.keys().at(i);
        if (_k.type() == QVariant::String) {
            QVariant _v = map[_k.toString()];
            if (_v.type() == QVariant::Map) {
                qDebug() << _k.toString() << ":map ==>";
                dumpVariantMap(_v.toMap());
            } else if (_v.type() == QVariant::List) {
                qDebug() << _k.toString() << ":list ==>";
                dumpVariantList(_v.toList());
            } else {
                if (_v.type() == QVariant::String) {
                    qDebug() << _k.toString() << "==>" << _v.toString();
                } else {
                    qDebug() << _k.toString() << "==>" << endl << _v;
                }
            }
        }
    }
}

void ReadJson::test()
{
    dump(mJson);
}
