/**
 * \file: travelthread.cpp
 */

#include "travelthread.h"
#include <QRegExp>

TravelThread::TravelThread(const QString& nm)
{
    qDebug() << Q_FUNC_INFO << "created, name:" << nm;

    currentFilter.clear();
    mFilelist.clear();
    mPathlist.clear();

    init_filter();
    shm = new QSharedMemory(SHMKEY, this);

    setThreadName(nm);
}

void TravelThread::init_filter()
{
    // QStringList _filter;

    // _filter << "*.mp3" << "*.wav" << "*.aac" << "*.m4a"
    //     << "*.wma" << "*.flac" << "*.ogg" << "*.ape";
    // filterHash.insert("music", _filter);

    // _filter.clear();
    // _filter << "*.mp4" << "*.wmv" << "*.mov" << "*.flv"
    //      << "*.mkv" << "*.avi" << "*.mpg" << "*.mpeg";
    // filterHash.insert("video", _filter);

    // _filter.clear();
    // _filter << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp"
    //      << "*.jpe";
    // filterHash.insert("picture", _filter);
}

bool TravelThread::isInBlacklist(const QString& name)
{
    if (name == "System Volume Information"
        || name == "lost+found"
        || name.contains(QRegExp("FOUND\\.\\d+"))
        || name == "$RECYCLE.BIN"
        || name == "Recycled"
    ) {
        return true;
    }
    return false;
}

void TravelThread::run()
{
    qDebug() << __PRETTY_FUNCTION__ << mThreadName << "running...";

    //currentFilter.clear();
    // if (!filterHash.contains(mThreadName)) {
    //     qWarning() << "no such filter for:" << mThreadName;
    //     emit sigThreadNotify(mThreadName);
    //     return;
    // }
    //currentFilter = filterHash.value(mThreadName);
    if (currentFilter.size() == 0) {
        qWarning() << "must set filter before running!";
        return;
    }

    qDebug() << "thread name:" << mThreadName << endl
        << "currentFilter:" << currentFilter;
    travel_dir(mStartpath);

    qDebug() << __PRETTY_FUNCTION__ << mThreadName << "finished...";

    mPathlist = mFolderHash.keys();
    report_status();
    emit filelistChanged();
    emit sigThreadNotify(mThreadName);
}

void TravelThread::travel_dir(const QString& path)
{
    QDir dir(path);

    //qDebug() << /* Q_FUNC_INFO << */ "path:" << path;
    if (isInBlacklist(dir.dirName())) {
        qDebug() << "skip:" << path;
        return;
    }

    QStringList *tmp = NULL;
    foreach (QString file, dir.entryList(currentFilter, QDir::Files | QDir::NoSymLinks)) {
        if ( !mFolderHash.contains(path) ) {
            tmp = new QStringList;
            mFolderHash.insert(path, tmp);
            int _fid = get_folderid();
            idh.mFolder2IdHash.insert(path, _fid);
            idh.mId2FolderHash.insert(_fid, path);
        }
        QFileInfo _info(dir, file);
        QString _fullfilepath = _info.filePath();
        mFilelist << _fullfilepath;
        (*tmp) << _fullfilepath;

        int _id = get_fileid();
        idh.mFile2IdHash.insert(_fullfilepath, _id);
        idh.mId2FileHash.insert(_id, _fullfilepath);
    }


    foreach (QString subDir, dir.entryList(QDir::Dirs
                                           | QDir::NoDotAndDotDot | QDir::NoSymLinks)) {
        travel_dir(path + QDir::separator() + subDir);
    }

}

void TravelThread::dumpFolderHash()
{
    qDebug() << Q_FUNC_INFO << "mFolderHash.size():" << mFolderHash.size();

    int count = 0;
    foreach (QString key, mFolderHash.keys()) {
        //qDebug() << "key:" << key;
        if (!QDir(key).exists()) {
            qDebug() << "path not found:" << key;
        }
        count += mFolderHash[key]->size();
    }
    if (mFilelist.size() != count) {
        qWarning() << "mismatched size!" << count;
    }
}

void TravelThread::clearFolderHash()
{
    foreach (QString key, mFolderHash.keys()) {
        delete mFolderHash[key];
    }
}

void TravelThread::report_status()
{
    qDebug() << Q_FUNC_INFO << endl
        << "mThreadName:" << mThreadName << endl
        << "mStartpath:" << mStartpath << endl
        << "mFilelist count:" << mFilelist.size() << endl
        << "mPathlist count:" << mPathlist.size();

}

void TravelThread::requestSave()
{
    qDebug() << Q_FUNC_INFO << "file2id size:"
        << idh.mFile2IdHash.size()
        << "folder2id size:"
        << idh.mFolder2IdHash.size();
    saveToShm(idh);
}

void TravelThread::requestLoad()
{
    IdHash ihh = loadFromShm();
    qDebug() << Q_FUNC_INFO << "file2id size:"
        << ihh.mFile2IdHash.size()
        << "folder2id size:"
        << ihh.mFolder2IdHash.size();
}

void TravelThread::saveToShm(const IdHash& idhash)
{
    qDebug() << __PRETTY_FUNCTION__;
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << idhash;
    int size = buffer.size();
    if (!shm->isAttached()) {
        qDebug() << "try to attach...";
        if (!shm->attach()) {
            qDebug() << "attach failed..." << shm->errorString();
            qDebug() << "try to create...";
            if (!shm->create(size)) {
                qDebug() << "create failed, will exit:" << shm->errorString();
                return;
            }
        }
    }
    if ( shm->lock() ) {
        char *to = (char*)shm->data();
        const char *from = buffer.data().data();
        QString md5 = md5sum(from, size);
        memcpy(to, from, qMin(shm->size(), size));
        qDebug() << "obj >> shm, md5sum:" << md5;
    }
    shm->unlock();
}

IdHash TravelThread::loadFromShm()
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!shm->isAttached()) {
        if (!shm->attach()) {
            qDebug() << "Unable to attach... will exit:" << shm->errorString();
            return IdHash();
        }
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    IdHash idh;
    if ( shm->lock() ) {
        buffer.setData((char*)shm->constData(), shm->size());
        buffer.open(QBuffer::ReadOnly);
        QString md5 = md5sum((const char*)shm->constData(), shm->size());
        in >> idh;
        qDebug() << "shm >> obj, md5sum:" << md5;
    }
    shm->unlock();
    return idh;
}

quint32 TravelThread::get_folderid()
{
    quint32 type = 0x200000;
    quint32 r = type | curr_folderid;
    curr_folderid ++;
    if (curr_folderid >= 1 || curr_folderid <= 0x1fffff ) {
        return r;
    } else {
        qWarning() << "out of bound!";
        return 0;
    }
}

quint32 TravelThread::get_fileid()
{
    quint32 type = 0x400000;
    quint32 r = type | curr_fileid;
    curr_fileid ++;
    if (curr_fileid >= 1 || curr_fileid <= 0x1fffff) {
        return r;
    } else {
        qWarning() << "out of bound!";
        return 0;
    }
}
