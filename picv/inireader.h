/**
 * \file inireader.h
 */

#ifndef __INI_READER_H__
#define __INI_READER_H__

#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QDebug>

#define DEFAULT_INI_PATH "/tmp/picture_out.ini"

class IniReader
{
public:
    static IniReader* getInstance();

    bool isActive() {
        return bActive;
    }

    bool startRead();
    QString requestById(int id);
    QString requestBySmallId(int id);

protected:
    static IniReader* _instance;
    IniReader();

    bool init_reader();

private:
    QSettings* ini = NULL;
    bool bActive = false;
    int basefileid = -1;
    int filecount = -1;
};


#endif // __INI_READER_H__
