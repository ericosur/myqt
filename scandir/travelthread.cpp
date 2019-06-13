/**
 * \file: travelthread.cpp
 */

#include "travelthread.h"

#include <QRegExp>
#include <QSettings>
#include <QTextCodec>
#include <QDateTime>

TravelThread::TravelThread(const QString& nm)
{
    qDebug() << Q_FUNC_INFO << "created, name:" << nm;

    currentFilter.clear();
    mFilelist.clear();
    mPathlist.clear();

    shm = new QSharedMemory(SHMKEY, this);

    setThreadName(nm);
    init();
}

void TravelThread::init()
{
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
    //report_status();
    dumpFolderHashToIni();
    //dumpIdh();
    //dumpIdHashToIni();

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

    QStringList *tmp = nullptr;
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
        qDebug() << "_fullfilepath:" << _fullfilepath;
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
        if ( mFolderHash[key]->size() ) {
            QStringList* sl = mFolderHash[key];
            for (int ii=0; ii<sl->size(); ++ii) {
                qDebug() << QString("%1: %2")
                    .arg(ii).arg(sl->at(ii));
            }
        }
    }
    if (mFilelist.size() != count) {
        qWarning() << "mismatched size!" << count;
    }
}

// void TravelThread::dumpIdHashToIni()
// {
//     QString fn = QString("%1/%2_id.ini").arg(mOutputDir).arg(mThreadName);
//     qDebug() << Q_FUNC_INFO << "to:" << fn;
//     QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//     QSettings st(fn, QSettings::IniFormat);
//     st.setIniCodec(codec);
//     st.clear();

//     qint64 time = QDateTime::currentMSecsSinceEpoch();
//     st.setValue("/start_time", QString::number(time));
//     qDebug() << time;

//     foreach (int id, idh.mId2FileHash.keys()) {
//         st.setValue(QString("/fileid/%1").arg(id), idh.mId2FileHash.value(id));
//     }
//     foreach (int id, idh.mId2FolderHash.keys()) {
//         st.setValue(QString("/folderid/%1").arg(id), idh.mId2FolderHash.value(id));
//     }

//     time = QDateTime::currentMSecsSinceEpoch();
//     st.setValue("/end_time", QString::number(time));
//     qDebug() << time;
// }

void TravelThread::dumpFolderHashToIni()
{
    QString fn = QString("%1/%2_out.ini").arg(mOutputDir).arg(mThreadName);
    qDebug() << Q_FUNC_INFO << "to:" << fn;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings st(fn, QSettings::IniFormat);
    st.setIniCodec(codec);
    st.clear();

    qint64 time = QDateTime::currentMSecsSinceEpoch();
    st.setValue("/start_time", QString::number(time));
    //st.setValue("/start_time", QTime::currentTime().toString("HH:mm:ss.zzz"));
    // thread name: [video, picture, music]
    st.setValue("/thread/mThreadName", mThreadName);
    st.setValue("/thread/mStartpath", mStartpath);
    st.setValue("/thread/mOutputDir", mOutputDir);
    st.setValue("/thread/BASE_DIRID", BASE_DIRID);
    st.setValue("/thread/BASE_FILEID", BASE_FILEID);

    // how many folders?
    if (mFolderHash.contains(mStartpath)) {
        // rootdir contains media files
        st.setValue("/size", mFolderHash.size()-1);
    } else {
        st.setValue("/size", mFolderHash.size());
    }

    st.setValue("/rootdir", mStartpath);

    if (mFolderHash.size() <= 0) {
        qWarning() << "folder hash list is empty:" << mThreadName;
        //mutex.unlock();
        return;
    }

    // process rootfolder first
    QString group_name;
    QString folder_name;
    QString key_name;

    int root_size = 0;

    if (mFolderHash.contains(mStartpath)) {
        QStringList *rf = mFolderHash.value(mStartpath);
        st.setValue("/rootdir/fileno", rf->size());
        st.setValue("/rootdir/dirno", mFolderHash.size()-1);
        root_size = rf->size() + mFolderHash.size() - 1;
        for (int ii = 0; ii<rf->size(); ii++) {
            QString fn = rf->at(ii);
            st.setValue(QString("/rootdir/f%1").arg(ii), fn);
            if (idh.mFile2IdHash.contains(fn)) {
                st.setValue(QString("/rootdir/fileid%1").arg(ii), idh.mFile2IdHash.value(fn));
            }
        }
    } else {
        st.setValue("/rootdir/dirno", mFolderHash.size());
        root_size = mFolderHash.size();
        qWarning() << "no files at rootdir...";
    }

    st.setValue("/rootdir/totalsize", root_size);


    QStringList folderkeylist = mFolderHash.keys();
    // because I will filter out "rootdir",
    // so the index dd will not the same as ii
    int dd = 0;
    for (int i = 0; i < folderkeylist.size(); i++) {
        group_name = QString("/folder%1").arg(dd);
        folder_name = folderkeylist.at(i);
        key_name = QString("%1/foldername").arg(group_name);
        st.setValue(key_name, folder_name);
        // special for root folder list ---
        if (folder_name != mStartpath) {
            st.setValue(QString("/rootdir/folder%1").arg(dd), folder_name);
            key_name = QString("/folder%1").arg(dd);
            st.setValue(key_name, folder_name);
            if (idh.mFolder2IdHash.contains(folder_name)) {
                st.setValue(QString("/folderid%1").arg(dd), idh.mFolder2IdHash.value(folder_name));
                st.setValue(QString("/folder%1/%2").arg(dd).arg("/folderid"), idh.mFolder2IdHash.value(folder_name));
                st.setValue(QString("/rootdir/folderid%1").arg(dd), idh.mFolder2IdHash.value(folder_name));
            }
            dd ++;
        } else {
            // will skip input_dir as a folder name,
            // it will go to special folder "rootdir"
            if (idh.mFolder2IdHash.contains(folder_name)) {
                st.setValue("/rootdir/folderid", idh.mFolder2IdHash.value(folder_name));
            }
        }
        // special for root folder list --->
        key_name = QString("%1/size").arg(group_name);
        QStringList* sl = mFolderHash.value(folder_name);
        st.setValue(key_name, sl->size());

        for (int j = 0; j < sl->size(); j++) {
            QString fn = sl->at(j);
            key_name = QString("%1/%2").arg(group_name).arg(j);
            st.setValue(key_name, fn);
            if (idh.mFile2IdHash.contains(fn)) {
                key_name = QString("%1/id%2").arg(group_name).arg(j);
                st.setValue(key_name, idh.mFile2IdHash.value(fn));
            } else {
                qWarning() << "not found in file2idhash!" << fn;
            }
        }
    }


    // dump all file id
    foreach (int id, idh.mId2FileHash.keys()) {
        st.setValue(QString("/fileid/%1").arg(id), idh.mId2FileHash.value(id));
        st.setValue(QString("/fileid/size"), idh.mId2FileHash.size());
    }
    // dump all folder id
    foreach (int id, idh.mId2FolderHash.keys()) {
        st.setValue(QString("/folderid/%1").arg(id), idh.mId2FolderHash.value(id));
        st.setValue(QString("/folderid/size"), idh.mId2FolderHash.size());
    }

    time = QDateTime::currentMSecsSinceEpoch();
    st.setValue("/end_time", QString::number(time));
    st.sync();
}

// void TravelThread::dumpIdh()
// {
//     QString fn = QString("%1/%2_idh.txt")
//         .arg(mOutputDir)
//         .arg(mThreadName);
//     qDebug() << Q_FUNC_INFO << "fn:" << fn;
//     idh.dumpToFile(fn);
// }

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
    quint32 r = BASE_DIRID | curr_folderid;
    curr_folderid ++;
    if (curr_folderid >= 1 || curr_folderid <= MAX_NUMBER_EACH_ID ) {
        return r;
    } else {
        qWarning() << "out of bound!";
        return 0;
    }
}

quint32 TravelThread::get_fileid()
{
    quint32 r = BASE_FILEID | curr_fileid;
    curr_fileid ++;
    if (curr_fileid >= 1 || curr_fileid <= MAX_NUMBER_EACH_ID) {
        return r;
    } else {
        qWarning() << "out of bound!";
        return 0;
    }
}
