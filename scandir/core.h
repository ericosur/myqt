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
#include <QMutex>
#include <QDebug>

#include "travelthread.h"

#define DEFAULT_START_PATH  "/media/usb"
#define DEFAULT_OUTPUT_PATH  "/tmp"

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* getInstance();

    bool setConfigFilename(const QString& fn);
    bool setInputdir(const QString& fn);
    bool setOutputdir(const QString& fn);

    void start();

signals:
    void sigQuitapp();
    void sigStart();
    void sigScanFinish();
    void sigScanAbort();

public slots:
    void sltStart();
    void sltTravelFinished();
    void sltThreadNotify(const QString& name);
    void sltScanFinish();
    void sltScanAbort();

protected:
    static Core* _instance;
    Core();

    void startThreads();
    //void dumpFolderHash(const QString& name, const FolderHashList& folderhash);
    void record_md5sum(const QString& name);

private:
    QString config_fn;
    QString input_dir;
    QString output_dir;
    quint32 basedirid;
    quint32 basefileid;

    QHash<QString, TravelThread*> threadHash;
    QMutex mutex;
};


#endif  // __CORE__H__
