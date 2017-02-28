#ifndef __TRAVEL_THREAD_H__
#define __TRAVEL_THREAD_H__

#include <QObject>
#include <QThread>
#include <QDir>
#include <QStringList>
#include <QHash>
#include <QDataStream>
#include <QBuffer>
#include <QSharedMemory>
#include <QDebug>

#include "miscutil.h"
#include "idhash.h"

typedef QHash<QString, QStringList*> FolderHashList;
#define SHMKEY    "travel.dir.sharedmem.key"


class TravelThread : public QThread
{
    Q_OBJECT

    Q_PROPERTY(QStringList filelist READ filelist WRITE setFilelist NOTIFY filelistChanged)

public:
    QStringList filelist() const {
        return mFilelist;
    }
    void setFilelist(const QStringList& sl) {
        mFilelist = sl;
        emit filelistChanged();
    }

public:
    TravelThread(const QString& nm = "null");
    void run();

    void setThreadName(const QString& nm) {
        mThreadName = nm;
    }
    QString getThreadName() const {
        return mThreadName;
    }
    void setStartPath(const QString& startpath) {
        mStartpath = startpath;
    }
    QString getStartPath() const {
        return mStartpath;
    }
    QStringList getFilelist() const {
        return mFilelist;
    }
    QStringList getPathlist() {
        return mPathlist;
    }
    void setFilter(const QStringList sl) {
        currentFilter = sl;
    }
    QStringList getFilter() const {
        return currentFilter;
    }

    FolderHashList getFolderhash() {
        return mFolderHash;
    }

    IdHash getIdHash() {
        return idh;
    }

    void requestSave();
    void requestLoad();

    void dumpFolderHash();
    void clearFolderHash();
    void report_status();

signals:
    void filelistChanged();
    void sigThreadNotify(const QString& s);

protected:
    void init_filter();
    bool isInBlacklist(const QString& name);
    void travel_dir(const QString& path);

    void saveToShm(const IdHash& hash);
    IdHash loadFromShm();

    quint32 get_folderid();
    quint32 get_fileid();

private:
    QString mThreadName = "null";
    QString mStartpath = "";

    //QHash<QString, QStringList> filterHash;
    QStringList currentFilter;

    QStringList mFilelist;  // list with all folders/files
    QStringList mPathlist;  // list with all folders

    quint32 curr_folderid = 1;    // start from 1
    quint32 curr_fileid = 1;

    IdHash idh;

    // key is path name, value is a string list
    FolderHashList mFolderHash;

    QSharedMemory *shm = NULL;
};

#endif // __TRAVEL_THREAD_H__
