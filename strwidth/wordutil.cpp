#include "wordutil.h"

#include <QFont>
#include <QFontMetrics>
#include <QSize>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

WordUtil* WordUtil::_instance = NULL;
WordUtil* WordUtil::getInstance()
{
    if (_instance == NULL) {
        _instance = new WordUtil();
    }
    return _instance;
}

WordUtil::WordUtil()
{

}

void WordUtil::test()
{
    test_json();
}

void WordUtil::test0()
{
    QSize s;
    getStringWidth("hello world", s);
}

void WordUtil::test_json()
{
    const QString strdefjson = "../strdef.json";
    if (rj.loadFile(strdefjson)) {
        qDebug() << "[INFO] loaded...";
    } else {
        qDebug() << "[FAIL] failed";
    }

    QJsonObject o = rj.getJobject();
#if 0
    QStringList sl = o.keys();
    for (int i=0; i<sl.size(); ++i) {
        qDebug() << sl.at(i);
    }
#endif

    QJsonObject p = o["en_US"].toObject();
    QStringList pl = p.keys();
    QSize sz;
    for (int i = 0; i < pl.size(); ++i) {
        getStringWidth(p[pl.at(i)].toString(), sz);
    }
}

int WordUtil::getStringWidth(const QString& str, QSize& sz)
{
    QFont fnt(mFontName, mPixelSize);
    QFontMetrics fm(fnt);

    sz.setWidth(fm.width(str));
    sz.setHeight(fm.height());

    qDebug() << "string:" << str << "font vc1, width:" << sz.width() << "height:" << sz.height();

    return sz.width();
}
