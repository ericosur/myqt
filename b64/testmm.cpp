#include "testmm.h"



void testmm()
{
    QMultiMap<QString, QString> mm;

    mm.insertMulti("apple", "iphone 7");
    mm.insertMulti("apple", "iphone 8");
    mm.insertMulti("apple", "iphone X");
    mm.insert("ball", "points");

    qDebug() << "uniqueKeys:" << mm.uniqueKeys();
    for (int i = 0; i < mm.uniqueKeys().size(); i++) {
        QString kk = mm.uniqueKeys().at(i);
        //qDebug() << "kk:" << kk;
        QList<QString> vv = mm.values(kk);
        if (vv.size() > 1) {
            for (int j = 0; j < vv.size(); j++) {
                qDebug() << kk << ":" << vv.at(j);
            }
        } else {
            qDebug() << mm.value(kk);
        }
    }
}

