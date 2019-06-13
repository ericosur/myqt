/// \file core.h
///
#ifndef ___CORE__H___
#define ___CORE__H___


#include <QString>
#include <QStringList>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QDebug>

class Core
{
public:
    static Core* getInstance();

    void start();

protected:
    static Core* _instance;
    Core();

    void read_ini(const QString& fn);
    bool read_json(const QString& fn);
    bool read_jobj(const QJsonObject& obj);
private:
    QSettings* mIni = nullptr;
};

#endif
