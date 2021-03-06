#include <QDebug>
#include <QThread>
#include <QRegExp>

#include "travelthread.h"


TravelThread::TravelThread()
{
    qDebug() << Q_FUNC_INFO << "created";

    mFilter.clear();
    mFilelist.clear();
    mPathlist.clear();

    init_filter();
}

void TravelThread::init_filter()
{
    // mFilter << "*.mp3" << "*.wav" << "*.aac" << "*.m4a"
    //     << "*.wma" << "*.flac" << "*.ogg" << "*.ape"
    //     << "*.mp4" << "*.wmv" << "*.mov" << "*.flv"
    //     << "*.mkv" << "*.avi" << "*.mpg" << "*.mpeg"
    //     << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp"
    //     << "*.jpe" << "*.mid" << "*.amr";
    // mFilter << "*.mp3" << "*.wav" << "*.aac" << "*.m4a"
    //     << "*.wma" << "*.flac" << "*.ogg" << "*.ape";
    mAudioFilter << "*.mp3" << "*.wav" << "*.aac" << "*.m4a"
        << "*.wma" << "*.flac" << "*.ogg" << "*.ape";
    mPictureFilter << "*.png" << "*.jpg" << "*.bmp";
    mFilter = mPictureFilter;
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
    qDebug() << Q_FUNC_INFO << "running...";

    travel_dir(mStartpath);
    //mPathlist = collect_path(mFilelist);

    qDebug() << Q_FUNC_INFO << "finished...";
    report_status();
    emit filelistChanged();
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
    foreach (QString file, dir.entryList(mFilter, QDir::Files | QDir::NoSymLinks)) {
        if ( !mFolderHash.contains(path) ) {
            tmp = new QStringList;
            mFolderHash.insert(path, tmp);
        }
        QFileInfo _info(dir, file);

        QString _fullfilepath = _info.filePath();
        mFilelist << _fullfilepath;
        (*tmp) << _fullfilepath;

        int _id = get_id();
        mFile2IdHash.insert(_fullfilepath, _id);
        mId2FileHash.insert(_id, _fullfilepath);
    }


    foreach (QString subDir, dir.entryList(QDir::Dirs
                                           | QDir::NoDotAndDotDot | QDir::NoSymLinks)) {
        travel_dir(path + QDir::separator() + subDir);
    }

    mPathlist = mFolderHash.keys();
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

void TravelThread::dumpId()
{
    foreach (int key, mId2FileHash.keys()) {
        qDebug() << key << "->" << mId2FileHash.value(key);
    }
    foreach (QString key, mFile2IdHash.keys()) {
        qDebug() << key << "->" << mFile2IdHash.value(key);
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
        << "mStartpath:" << mStartpath << endl
        << "mFilelist count:" << mFilelist.size() << endl
        << "mPathlist count:" << mPathlist.size();

}

int TravelThread::get_id()
{
    return _id++;
}
