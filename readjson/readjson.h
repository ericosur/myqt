#ifndef __LIB__READJSON_H__
#define __LIB__READJSON_H__

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QJsonDocument>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ReadJson {
public:
    ReadJson();
    ReadJson(const QString& f);
    bool loadFile();
    bool loadFile(const QString& filename);
    bool saveFile();
    bool saveFile(const QString& filename);

    static bool loadFile(const QString& filename, QJsonObject& jsonobj);
    static bool loadFile(const QString& filename, QJsonObject& jsonobj, QByteArray& arr);
    static bool saveFile(const QString& filename, const QJsonObject& jsonobj);

    void test();

public:
    QString getVersion() const {
        return QString("libreadjson: built at %1 %2")
                      .arg(__DATE__).arg(__TIME__);
    }

    QJsonDocument getJdoc() const {
        return mJdoc;
    }
    QJsonObject getJobject() const {
        return mJson;
    }
    QVariant getVariant() const {
        return mJdoc.toVariant();
    }

    void setJobject(const QJsonObject& json) {
        mJson = json;
    }

    QJsonObject getLeafObject(const QString& path);
    QJsonObject getLeafNode(const QString& path, QString& lastname);
    QJsonValue getLeafValue(const QString& path);
    QJsonArray getLeafArray(const QString& path);
    QJsonObject getLeafArrayAt(const QString& path, int idx);

    QString getLeafString(const QString& path, const QString& defVal=QString());
    bool getLeafBool(const QString& path, const bool defVal=false);
    int getLeafInt(const QString& path, const int defVal=0);
    qint64 getLeafInt64(const QString& path, const qint64 defVal=0);

    // simple key/value query functions
    QString getString(const QString& key, const QString& defVal);
    QString getString(const QString& key) {
        return getString(key, QString());
    }
    bool getBool(const QString& key, const bool defVal);
    bool getBool(const QString& key) {
        return getBool(key, false);
    }
    int getInt(const QString& key, const int defVal);
    int getInt(const QString& key) {
        return getInt(key, 0);
    }
    qint64 getInt64(const QString& key, const qint64 defVal);
    qint64 getInt64(const QString& key) {
        return getInt64(key, 0);
    }


    bool setString(const QString& key, const QString& val) {
        return ReadJson::setString(mJson, key, val);
    }
    bool setBool(const QString& key, const bool val) {
        return ReadJson::setBool(mJson, key, val);
    }
    bool setInt(const QString& key, const int val) {
        return ReadJson::setInt(mJson, key, val);
    }
    bool setInt64(const QString& key, const qint64 val) {
        return ReadJson::setInt64(mJson, key, val);
    }

    // below functions will effect json object within class ReadJson
    QJsonObject setLeafValue(const QString& path, const QJsonValue& value);
    QJsonObject setLeafArray(const QString& path, const QJsonArray& array);
    QJsonObject setLeafArray(const QString& path, const QStringList& slist);
    QJsonObject setLeafInt(const QString& path, int value);


    QString getFullJsonAsString() const {
        return mJsonString;
    }

    QMap<QString, QString> getMapFromList(const QStringList sl);
    void dumpJsonObjToDebug(const QJsonObject& obj);
    QString dumpJsonObjToString(const QJsonObject& obj);
    void dump();

    static QString getString(const QJsonObject& o, const QString& key, const QString& defVal=QString());
    static bool getBool(const QJsonObject& o, const QString& key, const bool defVal=false);
    static int getInt(const QJsonObject& o, const QString& key, const int defVal=0);
    static qint64 getInt64(const QJsonObject& o, const QString& key, const qint64 defVal=0);

    static bool setString(QJsonObject& o, const QString& key, const QString& val);
    static bool setBool(QJsonObject& o, const QString& key, const bool val);
    static bool setInt(QJsonObject& o, const QString& key, const int val);
    static bool setInt64(QJsonObject& o, const QString& key, const qint64 val);

    static void dump(const QJsonObject &json);
    static void dumpVariantList(const QVariantList& lst);
    static void dumpVariantMap(const QVariantMap& map);
    static bool readFileToByteArray(QByteArray& arr, const QString& fn);

protected:
    QJsonObject fetchdownlevel(const QJsonObject &json, const QString& lhs, QString& rhs);
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs);
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rootkey, QString& rhs);
    QString getLhs(const QString& input);
    QString getRhs(const QString& input);
    void checkValueType(const QJsonValue& v);

    QJsonObject buildjsonpath(const QString& path);
    static void ensurepath(const QString& fn);
#if 0
    void testString();
    void testArray();
    void dumpOneArrayElem(const QJsonObject& o);
#endif

private:
    // json file name/path
    QString mFile;

    // whole json file as string
    QString mJsonString;

    // json document
    QJsonDocument mJdoc;

    // loaded json as QJsonObject
    QJsonObject mJson;
};

#endif // __LIB__READJSON_H__
