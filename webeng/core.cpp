#include "core.h"
#include "trypath.h"

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core() : readJson()
{
    qsrand((uint)QDateTime::currentMSecsSinceEpoch());
}

QQmlApplicationEngine* Core::getEngine()
{
    if (mEngine == NULL) {
        mEngine = new QQmlApplicationEngine;
    }
    return mEngine;
}

void Core::hello()
{
    qDebug() << "hello world!";
    readConfig();
}

QString Core::search_config(const QString& fn)
{
    QString result;
    QStringList _list;

    _list << "./" << "../" << "/tmp/";
    searchFileFromList(_list, fn, result);
    return result;
}

bool Core::readConfig()
{
    QString conf = search_config(DEFAULT_CONFIG_FILE);

    qDebug() << "read config from:" << conf;
    mStatus = readJson.loadFile(conf);

    if (mStatus) {
        //readJson.test();
        setJsonstring( readJson.getFullJsonAsString() );

        setDefault_right_url( readJson.getLeafString("default.right.url") );
        setDefault_right_name( readJson.getLeafString("default.right.name") );
        setDefault_left_url( readJson.getLeafString("default.left.url") );
        setDefault_left_name( readJson.getLeafString("default.left.name") );
        setLocal_left_url( readJson.getLeafString("local.left.url") );
        setLocal_right_url( readJson.getLeafString("local.right.url") );
    } else {
        qDebug() << __func__ << "failed to read setting...";
    }

    return true;
}

QString Core::getRandomUrl()
{
    QString result;
    if (mStatus) {

        QJsonValue val = readJson.getLeafValue("items");
        if (val.isArray()) {
            int maxsize = val.toArray().size();
            int random = qrand() % maxsize;
            //qDebug() << "random:" << random;
            result = val.toArray()[random].toObject()["url"].toString();
        }
        //result = readJson.getString( readJson.getLeafArrayAt("items", 0), "url" );
        qDebug() << __func__ << result;

    } else {
        qDebug() << "failed to read setting...";
    }

    return result;

}