/**
    \file commonutil.h
    \brief provides some common utility function here

    - macro SHOW_CURRECT_EPOCH() will show elapse time into qDebug()
    - myMessageOutput() is cusomized message handler function to redirect
        qDebug() info
**/
#ifndef __COMMONUTIL_H__
#define __COMMONUTIL_H__

#include <QtGlobal>

static const int WAIT_MSEC_LENGTH = 75;
static const int MAX_RETRY_TIMES = 4;
static const int MAX_ITEM = 5;

typedef enum enum_item_type {
    NO_ITEM = 97,
    AUDIO_ITEM = 101,
    FOLDER_ITEM = 103
} ItemType;


// macro to show epoch time elapse everywhere at c++ code
extern qint64 g_epoch_start;
#define SHOW_CURRENT_EPOCH()    \
	qDebug() << __FILE__ << "func:" << Q_FUNC_INFO << "#" << __LINE__ << "elapse:" << ( QDateTime::currentMSecsSinceEpoch() - g_epoch_start )

extern bool g_messageVerbose;
// customized message handler
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QString md5sum(const char* buf, int size);

void dump(unsigned char* buf, unsigned int size);

#endif  // __COMMONUTIL_H__
