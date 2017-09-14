#ifndef READJSON_H
#define READJSON_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class ReadJson {
public:
    ReadJson(const QString& f);
    bool loadFile();
    bool loadFile(const QString& filename);
    void read(const QJsonObject &json);
    void test();

private:
    QString getLeafString(const QString& path);
    QJsonObject getLeafObject(const QString& path);
    QJsonValue getLeafValue(const QString& path);

    QJsonObject fetchOneLevel(const QJsonObject &json, const QString& input, QString& rhs);
    QString getLhs(const QString& input);
    QString getRhs(const QString& input);
    void checkValueType(const QJsonValue& v);

    void testString();
    void testArray();

    void dumpForecastArrayElem(const QJsonObject& o);
    QString getString(const QJsonObject& o, const QString& key);

private:
    QString mFile;
    QJsonObject mJson;
};

#endif // READJSON_H
