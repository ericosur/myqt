#include "readi.h"

void test_read_ini()
{
    QString fn = INIPATH;
    if ( !QFile::exists(fn) ) {
        qWarning() << "ini not found:" << fn;
        return;
    }
    QSettings ini(fn, QSettings::IniFormat);
    QString dns = ini.value("DNS", "").toString();
    QString gw = ini.value("GW", "").toString();
    QString ip = ini.value("IP", "").toString();
    qDebug() << "dns:" << dns << endl
        << "gw:" << gw << endl
        << "ip:" << ip ;
}
