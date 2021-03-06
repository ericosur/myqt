#include <QCoreApplication>
#include "flowctrl.h"

FlowControl* FlowControl::_instance = nullptr;
FlowControl* FlowControl::getInstance()
{
    if (_instance == nullptr) {
        _instance = new FlowControl();
    }
    return _instance;
}

FlowControl::FlowControl()
{
    if (readthead == nullptr) {
        readthead = new ReadThread();
    }
    connect(readthead, SIGNAL(finished()), this, SLOT(sltReadFinished()));
    connect(this, SIGNAL(sigQuitApp()), qApp, SLOT(quit()));
    connect(this, SIGNAL(sigGetfolder()), this, SLOT(sltGetfolder()));
}

void FlowControl::start()
{
    qDebug() << Q_FUNC_INFO;

    if (mFileFinished == false) {
        check_shm();
        // issue an IPC to tell "generator" start send data...
        send_msgq(MESGQKEY_MONITOR, MESGQKEY_MESSAGE_TYPE, "start");
        readthead->setReadItemType(AUDIO_ITEM);
        readthead->setBufferAddr(mBuffer);
        readthead->start();
    }
}

void FlowControl::sltGetfolder()
{
    if (!mFileFinished) {
        qWarning() << "why? file transfer not done...";
        return;
    }
    if (mFolderFinished == false) {
        requestGetfolder();
    }
}

void FlowControl::requestGetfolder()
{
    qDebug() << Q_FUNC_INFO;

    check_shm();
    // issue an IPC to tell "generator" start send data...
    send_msgq(MESGQKEY_MONITOR, MESGQKEY_MESSAGE_TYPE, "getfolder");
    readthead->setReadItemType(FOLDER_ITEM);
    readthead->start();
}

void FlowControl::sltReadFinished()
{
    qDebug() << Q_FUNC_INFO;
    if (mFileFinished == false) {
        mFileFinished = true;
        emit sigGetfolder();
    } else if (mFolderFinished == false) {
        mFolderFinished = true;
    }

    if (mFileFinished && mFolderFinished) {
        emit sigQuitApp();
    }
}

void FlowControl::check_shm()
{
    // fill all zero into 0xff
    FileItem _fi;
    memset(&_fi, 0, sizeof(FileItem));
    if (util_shm_write(LOCAL_SHM_KEY, sizeof(FileItem), &_fi) < 0) {
        qWarning() << "shm write failed";
    }
    FileItem *buf = (FileItem*)util_shm_read(LOCAL_SHM_KEY, sizeof(FileItem));
    if (buf == nullptr) {
        qWarning() << "failed to read shm...";
        return;
    }
    mBuffer = buf;
    QString sum1 = md5sum((char*)&_fi, sizeof(FileItem));
    QString sum2 = md5sum((char*)buf, sizeof(FileItem));
    if (sum1 != sum2) {
        qWarning() << "mismatch md5sum!!!";
    } else {
        qDebug() << "md5sum:" << sum1;
    }
}
