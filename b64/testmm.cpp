#include "testmm.h"

#include <QString>
#include <QMultiMap>
#include <QDebug>


void test_multimap()
{
    QMultiMap<QString, QString> mm;

    // mm.insertMulti("apple", "iphone 7");
    // mm.insertMulti("ball", "points");
    // mm.insertMulti("apple", "iphone 8");
    // mm.insertMulti("apple", "iphone X");
    // mm.insertMulti("pineapple", "apple pen");

    mm.insert("apple", "iphone 7");
    mm.insert("ball", "points");
    mm.insert("apple", "iphone 8");
    mm.insert("apple", "iphone X");
    mm.insert("pineapple", "apple pen");

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

    qDebug() << "2nd test...";
    for (int i = 0; i < mm.keys().size(); i++) {
        QString kk = mm.keys().at(i);
        qDebug() << kk;
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

