/// \file core.cpp

#include "core.h"
#include "commonutil.h"

#define INI_PATH    "../playlist.ini"
#define OUT_JSON    "o.json"

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
}

void Core::start()
{
    //qDebug() << Q_FUNC_INFO;

    // read_ini(INI_PATH);
    // if (QFile::exists(OUT_JSON)) {
    //     read_json(OUT_JSON);
    // }
    //
    read_json("../foo.json");
}

void Core::read_ini(const QString& fn)
{
    if (mIni == NULL) {
        mIni = new QSettings(fn, QSettings::IniFormat);
    }
    mIni->setIniCodec("UTF-8");

    QJsonObject jo;

    QStringList sl = mIni->childGroups();
    for (int i=0; i<sl.size(); ++i) {
        //qDebug() << "group:" << sl.at(i);
        QJsonArray* ja = new QJsonArray();
        mIni->beginGroup(sl.at(i));
        QStringList kl = mIni->childKeys();
        for (int j=0; j<kl.size(); ++j) {
            //qDebug() << j << ":" << kl.at(j) << "==>" << mIni->value(kl.at(j));
            if (kl.at(j) == "total" || kl.at(j) == "playlistcount") {
                // skip
            } else {
                QString val = mIni->value(kl.at(j)).toString();
                ja->append( QJsonValue(val) );
            }
        }
        mIni->endGroup();
        jo.insert(sl.at(i), *ja);
        delete ja;
    }

    QJsonDocument jdoc(jo);
    writeByteArrayToFile(jdoc.toJson(), OUT_JSON);
}

bool Core::read_json(const QString& fn)
{
    QByteArray arr;
    QJsonDocument jdoc;
    QJsonParseError err;

    if (readFileToByteArray(arr, fn)) {
        jdoc = QJsonDocument::fromJson(arr, &err);
        if (err.error != QJsonParseError::NoError) {
            qDebug() << "json parse err:" << err.errorString();
            return false;
        }
        read_jobj( jdoc.object() );

        return true;
    } else {
        qDebug() << "readFileToByteArray() failed";
    }
    return false;
}

bool Core::read_jobj(const QJsonObject& obj)
{
    Q_UNUSED(obj);
    //qDebug() << Q_FUNC_INFO;

    QJsonObject foo = obj;
    QJsonArray arr = foo["nosuch"].toArray();

    arr.append(1999);
    foo["test"] = arr;
    qDebug() << foo;

    return true;
}
