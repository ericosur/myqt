/// \file core.h
///
#ifndef ___CORE__H___
#define ___CORE__H___


#include <QString>
#include <QStringList>
#include <QSettings>
#include <QSettings>
#include <QDebug>

class Core
{
public:
    static Core* getInstance();

    void start();

protected:
    static Core* _instance;
    Core();

    void read_ini(const QString& fn);

private:
    QSettings* mIni = NULL;
};

#endif
