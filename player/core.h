#ifndef __CORE_H__
#define __CORE_H__

#include <QString>
#include <QDebug>

#include "rcommon.h"
#include "basicplayer.h"
#include "musicplayer.h"
#include "videoplayer.h"

class Core
{
public:
    static Core* getInstance();
    BasicPlayer* getActivePlayer() const {
        return mActivePlayer;
    }

    void playFile(const QString& fname);
    void pause();

    // or status report...
    QString getReason() {
        return mReason;
    }

protected:
    Core() {}
    static Core* _instance;

    BasicPlayer* get_player(const QString& fname);

private:
    BasicPlayer* mActivePlayer = nullptr;
    QString mCurrentFile;
    QString mReason;
    RCommon mCd;
};

#endif  // __CORE_H__
