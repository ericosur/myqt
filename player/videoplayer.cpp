#include "videoplayer.h"

VideoPlayer* VideoPlayer::_instance = nullptr;
VideoPlayer* VideoPlayer::getInstance()
{
    if (_instance == nullptr) {
        _instance = new VideoPlayer();
    }
    return _instance;
}

VideoPlayer::VideoPlayer()
{

}

void VideoPlayer::playFile(const QString& fname)
{
    qDebug() << Q_FUNC_INFO << fname;
}

void VideoPlayer::pause()
{
    qDebug() << Q_FUNC_INFO;
}
