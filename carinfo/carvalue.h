#ifndef __CAR_VALUES_H__
#define __CAR_VALUES_H__

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

#include "readjson.h"

#define DEFAULT_JSONFILE    "car-info.json"

class CarValue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(int enginetemp READ enginetemp NOTIFY enginetempChanged)
    Q_PROPERTY(double maf READ maf NOTIFY mafChanged)
    Q_PROPERTY(double oxygen READ oxygen NOTIFY oxygenChanged)
public:
    int speed() const {
        return mSpeed;
    }
    double rpm() const {
        return mRpm;
    }
    int enginetemp() const {
        return mEngineTemp;
    }
    double maf() const {
        return mMaf;
    }
    double oxygen() const {
        return mOxygen;
    }

public:
    static CarValue* getInstance();
    bool load();
    void dump();

signals:
    void speedChanged();
    void rpmChanged();
    void enginetempChanged();
    void mafChanged();
    void oxygenChanged();

protected:
    static CarValue* _instance;
    CarValue();

    bool loadJsonFile(const QString& fn);

private:
    int mSpeed = 0;
    double mRpm = 0.0;
    int mEngineTemp = 0;
    double mMaf = 0.0;
    double mOxygen = 0.0;
};



#endif  // __CAR_VALUES_H__
