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
    QJsonValue getLeafValue(const QString& path);
    QJsonArray getLeafArray(const QString& path);
    QJsonObject getLeafArrayAt(const QString& path, int idx);
    QString getString(const QJsonObject& o, const QString& key);

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
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs);
    QString getLhs(const QString& input);
    QString getRhs(const QString& input);
    void checkValueType(const QJsonValue& v);

    bool readFileToByteArray(QByteArray& arr, const QString& fn);
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
