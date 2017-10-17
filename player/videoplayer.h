#ifndef __VIDEO_PLAYER_H__
#define __VIDEO_PLAYER_H__

#include "basicplayer.h"

class VideoPlayer : public BasicPlayer
{
public:
    static VideoPlayer* getInstance();

    // NOTE: this function should be virtual,
    // implements pure virtual function BasicPlayer::playFile()
    virtual void playFile(const QString& fname);

    virtual void pause();

    // NOTE: this function should be virtual
    virtual QString getName() {
        return "VideoPlayer";
    }

protected:
    VideoPlayer();
    static VideoPlayer* _instance;
};


#endif  // __VIDEO_PLAYER_H__
