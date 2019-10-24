#ifndef __CORE__H__
#define __CORE__H__

#include <QObject>
#include <QStringList>
#include <QList>
#include <QString>
#include <QTimer>
#include <QDebug>

#include "readjson.h"

class Core: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString basesvg READ basesvg WRITE setBasesvg NOTIFY basesvgChanged)
    Q_PROPERTY(QString leftsvg READ leftsvg WRITE setLeftsvg NOTIFY leftsvgChanged)
    Q_PROPERTY(QString rightsvg READ rightsvg WRITE setRightsvg NOTIFY rightsvgChanged)
    Q_PROPERTY(QString outsvg READ outsvg WRITE setOutsvg NOTIFY outsvgChanged)

private:
    const int TIMER_INTERVAL = 1000;
    const QString JSON_CONFIG = "/ssd/src/myqt/dom/config.json";

public:
    QString basesvg() const {
        return mBaseSvgPath;
    }
    void setBasesvg(const QString& url) {
        mBaseSvgPath = url;
        emit basesvgChanged();
    }
    QString leftsvg() const {
        return mLeftSvgPath;
    }
    void setLeftsvg(const QString& url) {
        mLeftSvgPath = url;
        emit leftsvgChanged();
    }
    QString rightsvg() const {
        return mRightSvgPath;
    }
    void setRightsvg(const QString& url) {
        mRightSvgPath = url;
        emit rightsvgChanged();
    }
    QString outsvg() const {
        return mOutSvgPath;
    }
    void setOutsvg(const QString& url) {
        mOutSvgPath = url;
        emit outsvgChanged();
    }

public:
    static Core* getInstance();
    void make_svg_command(const QString& cmd, int nth);

protected:
    static Core* _instance;
    Core();
    bool isGoRightLane(const QStringList& sl);

public slots:
    void sltTimeout();

signals:
    void basesvgChanged();
    void leftsvgChanged();
    void rightsvgChanged();
    void outsvgChanged();

private:
    QString mBaseSvgPath;
    QString mLeftSvgPath;
    QString mRightSvgPath;
    QString mOutSvgPath;

    QTimer* test_timer = nullptr;
    ReadJson rj;

    int exitNumber = -1;
    QString exitDirection;
    QList<int> exits;
};

#endif  // __CORE__H__
