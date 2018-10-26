/**
 * \file: waitbtthread.cpp
 */

#include "filelock.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>

void show_errno(int no)
{
#ifdef TEST_WAITBT
    QString s;
    switch(no) {
    case EBADF:
        s = "EBADF";
        break;
    case EINTR:
        s = "EINTR";
        break;
    case EINVAL:
        s = "EINVAL";
        break;
    case ENOLCK:
        s = "ENOLCK";
        break;
    case EWOULDBLOCK:
        s = "EWOULDBLOCK";
        break;
    default:
        break;
    }
    qDebug() << "errno:" << s;
#else
    Q_UNUSED(no);
#endif
/*
   EBADF  fd is not an open file descriptor.

   EINTR  While waiting to acquire a lock, the call was interrupted by
          delivery of a signal caught by a handler; see signal(7).

   EINVAL operation is invalid.

   ENOLCK The kernel ran out of memory for allocating lock records.

   EWOULDBLOCK
          The file is locked and the LOCK_NB flag was selected.
*/

}

// quint64 FileLock::getEpoch()
// {
//     return QDateTime::currentMSecsSinceEpoch();
// }


int FileLock::myflock(const char *name, int& fd)
{
    fd = open(name, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        qDebug() << "myflock failed to open file";
        return -1;
    }

    int ret = flock(fd, LOCK_EX | LOCK_NB);
    if (ret) {
        close(fd);
        show_errno(errno);
        if(EWOULDBLOCK == errno) {
#ifdef TEST_WAITBT
            qDebug() << "!!! file is used:" << name;
            //fprintf(stderr, "File %s is being used!!!\n", name);
#endif
            return ret;
        }

    } else {
#ifdef TEST_WAITBT
        qDebug() << "myflock: file: " << name << "fd:" << fd << "is locked";
#endif
    }
    // file is locked sucessfully
    return 0;
}

int FileLock::myfunlock(int& fd)
{
    int ret = -1;
    do {
        if (fd == -1) {
            // if (mDebugWaitBt)
            //     qDebug() << __func__ << "fileno is empty, skip...";
            break;
        }

        // will release file lock
        ret = flock(fd, LOCK_UN);
        if ( ret == 0 ) {
#ifdef TEST_WAITBT
            qDebug() << __func__ << "fd" << fd << "unlocked";
#endif
            close(fd);
            fd = -1;
        } else {
#ifdef TEST_WAITBT
            qWarning() << __func__ << "fd" << fd << "file unlock failed";
            // does not change fileno
            show_errno(errno);
#endif
        }
    } while (false);

    return ret;
}
