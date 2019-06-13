#include "core.h"

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

BasicPlayer* Core::get_player(const QString& fname)
{
    if (fname.contains("mp3")) {
        return MusicPlayer::getInstance();
    }
    if (fname.contains("mp4")) {
        return VideoPlayer::getInstance();
    }
    return nullptr;
}

void Core::playFile(const QString& fname)
{
    qDebug() << Q_FUNC_INFO << "fname:" << fname;
    BasicPlayer* ret = get_player(fname);
    if (ret == nullptr) {
        qDebug() << "cannot play:" << fname;
        // change current player to NULL
        mActivePlayer = nullptr;
        // should I change current file to fname?
        mCurrentFile = fname;
        mReason = "cannot play such file";
        qDebug() << "get status:" << mCd.getStatus();
    } else {
        mActivePlayer = ret;
        mActivePlayer->playFile(fname);
        mCurrentFile = fname;
        mReason = "playing";
    }
}

void Core::pause()
{
    qDebug() << Q_FUNC_INFO;
    if (mActivePlayer != nullptr) {
        mActivePlayer->pause();
    } else {
        qDebug() << "cannot pause because no active player";
    }
}
