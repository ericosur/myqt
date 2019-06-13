#include "core.h"
#include "readjson.h"

#include <QString>
#include <QDateTime>
#include <QDebug>

#define JSON_PATH   "../setting.json"


Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
    //qDebug() << Q_FUNC_INFO << "starts...";
}


QVariantMap Core::loadJsonToVmap(const QString& fn)
{
    if (fn.isEmpty()) {
        return QVariantMap();
    }

    QJsonObject jobj;
    if (!ReadJson::loadFile(fn, jobj)) {
        return QVariantMap();
    }
    jobj["extra"] = "insert from core";
    QVariantMap vmap = jobj.toVariantMap();
    return vmap;
}

void Core::test()
{
    qDebug() << Q_FUNC_INFO;
    QVariantMap vm = loadJsonToVmap(JSON_PATH);
    emit stateChanged(vm);
}
