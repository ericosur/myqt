#ifndef __LIB__READJSON_H__
#define __LIB__READJSON_H__

#include <QString>
#include <QStringList>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QIODevice>
#include <QDebug>

class ReadJson {
public:
    ReadJson();
    ReadJson(const QString& f);
    bool loadFile();
    bool loadFile(const QString& filename);
    bool saveFile(const QString& filename);
    static bool saveFile(const QString& filename, const QJsonObject& jsonobj);
    void test();

public:
    QString getVersion() const {
        return QString("libreadjson: built at %1 %2")
                      .arg(__DATE__).arg(__TIME__);
    }

    QJsonDocument getJdoc() {
        return mJdoc;
    }

    QJsonObject getJobject() {
        return mJson;
    }

    QString getLeafString(const QString& path);
    QJsonObject getLeafObject(const QString& path);
    QJsonObject getLeafObject(const QString& path, QString& lastname);
    QJsonValue getLeafValue(const QString& path);
    QJsonArray getLeafArray(const QString& path);
    QJsonObject getLeafArrayAt(const QString& path, int idx);
    QString getString(const QJsonObject& o, const QString& key);

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

    static void dump(const QJsonObject &json);
    static void dumpVariantList(const QVariantList& lst);
    static void dumpVariantMap(const QVariantMap& map);

protected:
    QJsonObject fetchdownlevel(const QJsonObject &json, const QString& lhs, QString& rhs);
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs);
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rootkey, QString& rhs);
    QString getLhs(const QString& input);
    QString getRhs(const QString& input);
    void checkValueType(const QJsonValue& v);

    bool readFileToByteArray(QByteArray& arr, const QString& fn);
    QJsonObject buildjsonpath(const QString& path);
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
