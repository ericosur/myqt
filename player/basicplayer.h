#ifndef __BASIC_PLAYER_H__
#define __BASIC_PLAYER_H__

#include <QString>
#include <QDebug>

class BasicPlayer
{
public:

    virtual void playFile(const QString& fname) = 0;
    virtual void pause() = 0;

    virtual QString getName() {
        return "BasicPlayer";
    }

protected:

private:

};


#endif  // __BASIC_PLAYER_H__
