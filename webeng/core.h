#ifndef __CORE__H__
#define __CORE__H__

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QDateTime>
#include <QDebug>

#include "readjson.h"

#define MIN_COREWIDTH       500
#define MIN_COREHEIGHT      600

class Core: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int coreWidth READ coreWidth WRITE setCoreWidth NOTIFY coreWidthChanged)
    Q_PROPERTY(int coreHeight READ coreHeight WRITE setCoreHeight NOTIFY coreHeightChanged)
    Q_PROPERTY(QString default_left_url READ default_left_url WRITE setDefault_left_url NOTIFY default_left_urlChanged)
    Q_PROPERTY(QString default_left_name READ default_left_name WRITE setDefault_left_name NOTIFY default_left_nameChanged)
    Q_PROPERTY(QString default_right_url READ default_right_url WRITE setDefault_right_url NOTIFY default_right_urlChanged)
    Q_PROPERTY(QString default_right_name READ default_right_name WRITE setDefault_right_name NOTIFY default_right_nameChanged)
    Q_PROPERTY(QString jsonstring READ jsonstring WRITE setJsonstring NOTIFY jsonstringChanged)

    Q_PROPERTY(QString local_left_url READ local_left_url WRITE setLocal_left_url NOTIFY local_left_urlChanged)
    Q_PROPERTY(QString local_right_url READ local_right_url WRITE setLocal_right_url NOTIFY local_right_urlChanged)

public:
    Q_INVOKABLE QString getRandomUrl();

    int coreWidth() const {
        return mCoreWidth;
    }
    void setCoreWidth(int w) {
        mCoreWidth = w;
        emit coreWidthChanged();
    }
    int coreHeight() const {
        return mCoreHeight;
    }
    void setCoreHeight(int h) {
        mCoreHeight = h;
        emit coreHeightChanged();
    }
    QString default_left_url() const {
        return mDefaultLeftUrl;
    }
    void setDefault_left_url(const QString& url) {
        mDefaultLeftUrl = url;
        emit default_left_url();
    }
    QString default_left_name() const {
        return mDefaultLeftName;
    }
    void setDefault_left_name(const QString& name) {
        mDefaultLeftName = name;
        emit default_left_name();
    }
    QString default_right_url() const {
        return mDefaultRightUrl;
    }
    void setDefault_right_url(const QString& url) {
        mDefaultRightUrl = url;
        emit default_right_url();
    }
    QString default_right_name() const {
        return mDefaultRightName;
    }
    void setDefault_right_name(const QString& name) {
        mDefaultRightName = name;
        emit default_right_name();
    }
    QString jsonstring() const {
        return mJsonString;
    }
    void setJsonstring(const QString& s) {
        mJsonString = s;
        emit jsonstringChanged();
    }

    QString local_left_url() const {
        return mLocalLeftUrl;
    }
    void setLocal_left_url(const QString& s) {
        mLocalLeftUrl = s;
        emit local_left_urlChanged();
    }
    QString local_right_url() const {
        return mLocalRightUrl;
    }
    void setLocal_right_url(const QString& s) {
        mLocalRightUrl = s;
        emit local_right_urlChanged();
    }

public:
    bool readConfig();

signals:
    void coreWidthChanged();
    void coreHeightChanged();
    void default_left_urlChanged();
    void default_right_urlChanged();
    void default_left_nameChanged();
    void default_right_nameChanged();
    void jsonstringChanged();
    void local_left_urlChanged();
    void local_right_urlChanged();

public:
    static Core* getInstance();
    void hello();
    QQmlApplicationEngine* getEngine();

protected:
    Core();
    static Core* _instance;

    QString search_config(const QString& fn);

private:
    QQmlApplicationEngine* mEngine = NULL;
    int mCoreWidth = MIN_COREWIDTH;
    int mCoreHeight = MIN_COREHEIGHT;

    ReadJson readJson;
    bool mStatus = false;
    QString mDefaultLeftUrl;
    QString mDefaultRightUrl;
    QString mDefaultLeftName;
    QString mDefaultRightName;
    QString mLocalLeftUrl;
    QString mLocalRightUrl;
    QString mJsonString;
};

#endif  // __CORE__H__
