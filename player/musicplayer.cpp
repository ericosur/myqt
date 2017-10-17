#include "musicplayer.h"

MusicPlayer* MusicPlayer::_instance = NULL;
MusicPlayer* MusicPlayer::getInstance()
{
    if (_instance == NULL) {
        _instance = new MusicPlayer();
    }
    return _instance;
}

MusicPlayer::MusicPlayer()
{

}

void MusicPlayer::playFile(const QString& fname)
{
    qDebug() << Q_FUNC_INFO << fname;
}

void MusicPlayer::pause()
{
    qDebug() << Q_FUNC_INFO;
}
