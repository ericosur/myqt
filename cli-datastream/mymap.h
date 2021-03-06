/**
  * \file mymap.h
**/

#ifndef __MY_MAP_H__
#define __MY_MAP_H__

#include <QObject>
#include <QString>
#include <QDataStream>
#include <QList>
#include <QVariantMap>

class MyMap
{
public:
    MyMap();

    //void setMap(const QMap<QString, int>& m);
    void init();
    void dump();
    void save();
    void load();

protected:
    friend QDataStream& operator<<(QDataStream& ds, const MyMap& obj);
    friend QDataStream& operator>>(QDataStream& ds, MyMap& obj);

private:
    const QString MYMAPFILE = "/tmp/mymap.dat";

    QList<QVariantMap> scannedDevices;
};



#endif  // __MY_MAP_H__