#ifndef __COMMON_FILE_LOCK_H__
#define __COMMON_FILE_LOCK_H__

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QFile>
#include <QThread>
#include <QTimer>
#include <QDebug>

//#define TEST_WAITBT

class FileLock : public QObject
{
    Q_OBJECT

public:
    FileLock() {}

    static int myflock(const char *name, int& fd);
    static int myfunlock(int& fd);

};

#endif // __COMMON_FILE_LOCK_H__
