#include "core.h"
#include "trypath.h"

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
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
    if (mEngine == nullptr) {
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

void Core::setLocal_left_url(const QString& s)
{
    bool bApply = false;

    if (s.contains("file://")) {
        bApply = check_local_file(s);
    } else {
        bApply = true;
    }

    if (bApply) {
        mLocalLeftUrl = s;
        emit local_left_urlChanged();
    }
}

void Core::setLocal_right_url(const QString& s)
{
    bool bApply = false;

    if (s.contains("file://")) {
        bApply = check_local_file(s);
    } else {
        bApply = true;
    }

    if (bApply) {
        mLocalRightUrl = s;
        emit local_right_urlChanged();
    }
}

bool Core::check_local_file(const QString& path)
{
    QUrl url(path);

    if (url.isLocalFile()) {
        QString localf = url.toLocalFile();
        if (!QFile::exists(localf)) {
            qWarning() << "specified local url not found:" << path;
            return false;
        } else {
            return true;
        }
    } else {
        qWarning() << "not a local url";
        return false;
    }
}
