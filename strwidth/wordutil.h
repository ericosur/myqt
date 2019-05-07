#ifndef __UTIL_WORDUTIL__
#define __UTIL_WORDUTIL__

#include <QSize>
#include <QString>
#include <QDebug>

#include "readjson.h"

class WordUtil : public QObject
{
public:
    static WordUtil* getInstance();
    int getStringWidth(const QString& str, QSize& sz);

    void setFontPixelSize(int s) {
        mPixelSize = s;
    }
    void setFontName(const QString& fn) {
        mFontName = fn;
    }

    void test();

    void test0();
    void test_json();

protected:
    static WordUtil* _instance;
    WordUtil();

private:
    ReadJson rj;
    int mPixelSize = 24;
    QString mFontName = "VC1";
};




#endif  // __UTIL_WORDUTIL__
