/// file: nowplaycore.h
#ifndef __NOWPLAYING_CORE_H__
#define __NOWPLAYING_CORE_H__

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "pollthread.h"

class NowPlayingCore : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString jsonstring READ jsonstring WRITE setJsonstring NOTIFY jsonstringChanged)

#if 0
    Q_PROPERTY(int coreWidth READ coreWidth WRITE setCoreWidth NOTIFY coreWidthChanged)
    Q_PROPERTY(int coreHeight READ coreHeight WRITE setCoreHeight NOTIFY coreHeightChanged)
    Q_PROPERTY(QString default_left_url READ default_left_url WRITE setDefault_left_url NOTIFY default_left_urlChanged)
    Q_PROPERTY(QString default_left_name READ default_left_name WRITE setDefault_left_name NOTIFY default_left_nameChanged)
    Q_PROPERTY(QString default_right_url READ default_right_url WRITE setDefault_right_url NOTIFY default_right_urlChanged)
    Q_PROPERTY(QString default_right_name READ default_right_name WRITE setDefault_right_name NOTIFY default_right_nameChanged)

    Q_PROPERTY(QString local_left_url READ local_left_url WRITE setLocal_left_url NOTIFY local_left_urlChanged)
    Q_PROPERTY(QString local_right_url READ local_right_url WRITE setLocal_right_url NOTIFY local_right_urlChanged)
#endif

public:
    static NowPlayingCore* getInstance();

    QString loadJson(const QString& fn);

protected:
    static NowPlayingCore* _instance;
    NowPlayingCore();

    QString jsonstring() {
        return json_string;
    }
    void setJsonstring(const QString& s) {
        json_string = s;
        emit jsonstringChanged();
    }

signals:
    void jsonstringChanged();
    void lhsChanged();
    void rhsChanged();

public slots:
    void sltPollTimeout();
    void sltLhsChanged();
    void sltRhsChanged();

private:
    QString json_string;
    PollThread* pt = nullptr;
};

#endif  // __NOWPLAYING_CORE_H__
