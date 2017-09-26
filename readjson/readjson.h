#ifndef __LIB__READJSON_H__
#define __LIB__READJSON_H__

#include <QString>
#include <QStringList>
#include <QMap>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ReadJson {
public:
    ReadJson();
    ReadJson(const QString& f);
    bool loadFile();
    bool loadFile(const QString& filename);
    void read(const QJsonObject &json);

public:
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
    void dumpJsonObj(const QJsonObject& obj);

protected:
    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs);
    QString getLhs(const QString& input);
    QString getRhs(const QString& input);
    void checkValueType(const QJsonValue& v);

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
    // loaded json as QJsonObject
    QJsonObject mJson;
};

#endif // __LIB__READJSON_H__