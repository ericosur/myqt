#ifndef __CORE__H__
#define __CORE__H__

#include <QObject>
#include <QString>
#include <QStringList>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QTextCodec>
#include <QHash>
#include <QDebug>

#include "travelthread.h"

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* getInstance();

    void setConfigFilename(const QString& fn);
    void setInputdir(const QString& fn);
    void setOutputdir(const QString& fn) {
        output_dir = fn;
    }

    void start();

signals:
    void sigQuitapp();
    void sigStart();

public slots:
    void sltStart();
    void sltTravelFinished();
    void sltThreadNotify(const QString& name);

protected:
    static Core* _instance;
    Core();

    void startThreads();

private:
    QString config_fn;
    QString input_dir;
    QString output_dir;

    QHash<QString, TravelThread*> threadHash;
};


#endif  // __CORE__H__
