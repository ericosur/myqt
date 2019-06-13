#include "nowplaycore.h"
#include "readjson.h"

#include <QString>
#include <QDateTime>
#include <QDebug>

#define JSON_PATH_LHS   "/home/rasmus/src/myqt/readjson/nowplaying/lhs.json"
#define JSON_PATH_RHS   "/home/rasmus/src/myqt/readjson/nowplaying/rhs.json"

NowPlayingCore* NowPlayingCore::_instance = nullptr;
NowPlayingCore* NowPlayingCore::getInstance()
{
    if (_instance == nullptr) {
        _instance = new NowPlayingCore();
    }
    return _instance;
}

NowPlayingCore::NowPlayingCore()
{
    qDebug() << Q_FUNC_INFO << "starts...";
    pt = new PollThread();
    connect(pt, SIGNAL(sigPollTimeout()), this, SLOT(sltPollTimeout()));

    connect(pt, SIGNAL(sigRhsChanged()), this, SLOT(sltRhsChanged()));
    connect(pt, SIGNAL(sigLhsChanged()), this, SLOT(sltLhsChanged()));

    pt->start();
}

QString NowPlayingCore::loadJson(const QString& fn)
{
    qDebug() << Q_FUNC_INFO;
    ReadJson j;
    if (j.loadFile(fn)) {
        json_string = j.getFullJsonAsString();
        emit jsonstringChanged();
        return json_string;
    }
    qWarning() << "loadJson(): something wrong";
    return QString();
}

void NowPlayingCore::sltPollTimeout()
{
    qint64 current = QDateTime::currentMSecsSinceEpoch();
    qDebug() << Q_FUNC_INFO << current;
}

void NowPlayingCore::sltLhsChanged()
{
    loadJson(JSON_PATH_LHS);
    emit lhsChanged();
}

void NowPlayingCore::sltRhsChanged()
{
    loadJson(JSON_PATH_RHS);
    emit rhsChanged();
}
