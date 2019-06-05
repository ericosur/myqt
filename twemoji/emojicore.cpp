#include "emojicore.h"

#include <QString>
#include <QRegularExpression>
#include <QByteArray>
#include <QDebug>

EmojiCore* EmojiCore::_instance = NULL;

EmojiCore* EmojiCore::getInstance()
{
    if (_instance == NULL) {
        _instance = new EmojiCore();
    }
    return _instance;
}


EmojiCore::EmojiCore(QObject *_parent) : QObject(_parent)
{
    qDebug() << __func__ << "number of emojList:" << emojiList.size();
    test();
    qDebug() << "=========";
    test1();
}

void EmojiCore::test1()
{
    QStringList sl = {
        "1f1e7", "1f1ff", "1f365", "39", "20e3", "26f9", "fe0f",
        "200d", "2642", "fe0f", "26bd", "23", "20e3",
    };
    parse(sl);
}

// NOTE: if pop char is U+FE0F, should drop it
void EmojiCore::parse(const QStringList& strlist)
{
    QStringList sl = strlist;
    QRegularExpression re;
    QStringList matchList;
    QString foo;
    int fuck = 0;
    bool canTry = false;
    QStringList ans;

    // takeFirst
    while (!sl.isEmpty()) {
        foo = "";

        ans.clear();
        QString cc = sl.takeFirst();
        //qDebug() << "curr:" << cc;

        QString tmp = QString("^") + cc;
        re = QRegularExpression(tmp);

        do {
            //qDebug() << "re =====> " << re.pattern();
            matchList = emojiList.filter(re);
            //qDebug() << "matchList ===>" << matchList;
            if (matchList.isEmpty()) {
                if (!ans.isEmpty()) {
                    qDebug() << "pop ans:" << ans;
                }
                if (!cc.isEmpty()) {
                    qDebug() << "pop cc:" << cc;
                }

                ans.clear();
                canTry = false;
                break;
            } else {
                fuck ++;
                //qDebug() << "matched:" << matchList;
                if (matchList.size() == 1) {
                    qDebug() << "ans:" << matchList[0];
                    canTry = false;
                    break;
                } else {
                    canTry = true;
                    foo = tmp;
                }

                if (!sl.isEmpty()) {
                    tmp = foo + QString("-") +  sl.takeFirst();
                    re = QRegularExpression(tmp);
                    matchList.clear();
                    canTry = true;
                } else {
                    canTry = false;
                }
            }
        } while (canTry && fuck < 10);

    }



}

void EmojiCore::test()
{
    unsigned char buf[] = {
        0xe6, 0x88, 0x91,
        0xe2, 0x9d, 0xa4, 0xef, 0xb8, 0x8f, 0xf0, 0x9f,
        0x87, 0xa7, 0xf0, 0x9f, 0x87, 0xb4,
        0xe4, 0xb9, 0x9f, 0xe6, 0x84, 0x9b,
        0xf0, 0x9f,
        0x99, 0x8b, 0xe2, 0x80, 0x8d, 0xe2, 0x99, 0x80,
        0xef, 0xb8, 0x8f,
        0xe7, 0x8e, 0xa9,
        0xf0, 0x9f, 0x8f, 0x88, 0xef, 0xbc, 0x8c, 0xe7,
        0x9c, 0x9f,
        0xf0, 0x9f, 0x98, 0x83, 0x00
    };

    QStringList sl;
    setSequence(QString::fromUtf8((const char*)buf));
    int p = 0;
    while (p < mSeq.count()) {
        QChar cc = mSeq[p];

        if (cc.isHighSurrogate()) {
            //qDebug() << cc << "isHighSurrogate";
            p ++;
            QChar dd = mSeq[p];
            if (!dd.isLowSurrogate()) {
                qDebug() << "why?" << cc;
            } else {
                uint codepoint = QChar::surrogateToUcs4(cc, dd);
                //qDebug() << "codepoint:" << QString::number(codepoint, 16);
                sl << QString::number(codepoint, 16);
            }
        } else if (cc.isLowSurrogate()) {
            qDebug() << "why?" << cc << "isLowSurrogate";
        } else {
            //qDebug() << QString::number(cc.unicode(), 16);
            sl << QString::number(cc.unicode(), 16);
        }
        p ++;
    }
    qDebug() << "sl:" << sl;
    parse(sl);

}
