#ifndef __MUSIC_PLAYER_H__
#define __MUSIC_PLAYER_H__

#include "basicplayer.h"

class MusicPlayer : public BasicPlayer
{
public:
    static MusicPlayer* getInstance();

    // NOTE: this function should be virtual,
    // implements pure virtual function BasicPlayer::playFile()
    void playFile(const QString& fname);

    virtual void pause();

    // NOTE: this function should be virtual
    virtual QString getName() {
        return "MusicPlayer";
    }

protected:
    MusicPlayer();
    static MusicPlayer* _instance;
};


#endif  // __MUSIC_PLAYER_H__
