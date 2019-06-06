#include "emojicore.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

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

    load_tests();

    test_timer = new QTimer(this);
    connect(test_timer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
    test_timer->setSingleShot(true);
    test_timer->setInterval(2000);
    test_timer->start();

    //test0();
}

void EmojiCore::load_tests()
{
    using namespace std;
    using namespace nlohmann;
    string json_file = "../emoji_tests.json";
    try {
        ifstream inf(json_file);
        json j;
        inf >> j;

        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            json j_string = (*it);
            test_list << QString::fromStdString(j_string.get<std::string>());
        }
    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    }
}

void EmojiCore::sltTimeout()
{
    qDebug() << __func__;
    if (!test_list.isEmpty()) {
        QStringList sl = string_to_codepoint_list(test_list.takeFirst());
        QString ans = parse_codepoint_list(sl);
        qDebug() << ans;
        setSequence(ans);

        test_timer->setSingleShot(true);
        test_timer->start();
    }
}

// NOTE: if pop char is U+FE0F, should drop it
QString EmojiCore::parse_codepoint_list(const QStringList& strlist)
{
    qDebug() << __func__ << "input sl:" << strlist;
    QStringList sl = strlist;
    QRegularExpression re;
    QStringList matchList;
    QString foo;
    bool canTry = false;
    QString shouldSkip;
    QString ans;
    bool bDebug = true;
    bool ok;
    const int IMG_WIDTH = 28;
    const int IMG_HEIGHT = 28;

    // takeFirst
    while (!sl.isEmpty()) {
        foo = "";

        QString cc = sl.takeFirst();
        if (bDebug)  qDebug() << "curr:" << cc;
        if (cc == shouldSkip) {
            qDebug() << "skip this cc," << cc;
            shouldSkip = "";
            continue;
        }
        // exception: direct add into ans
        int cp = cc.toInt(&ok, 16);
        if (cp < 0xa9) {
            ans += QChar(cp);
            continue;
        }

        QString tmp = QString("^") + cc;
        re = QRegularExpression(tmp);

        do {
            if (bDebug)  qDebug() << "try re =====> " << re.pattern();
            matchList = emojiList.filter(re);
            if (bDebug)  qDebug() << "matchList ===>" << matchList;
            if (matchList.isEmpty()) {
                if (!cc.isEmpty() && cc != "fe0f") {
                    if (bDebug)  qDebug() << "pop cc:" << cc;
                    ans += QChar(cc.toInt(&ok, 16));
                }
                canTry = false;
                break;
            } else {
                qDebug() << "matched:" << matchList;
                if (matchList.size() == 1) {
                    QString t = matchList[0];
                    QString imgsrc = QString(
                        "<img height=\"%1\" width=\"%2\"src=\"72x72/%3.png\">").arg(IMG_HEIGHT).arg(IMG_WIDTH).arg(t);
                    qDebug() << "matched img:" << t;

                    int idx = t.lastIndexOf("-");
                    if (idx != -1) {
                        shouldSkip = t.right(t.size()-idx-1);
                        if (bDebug)  qDebug() << "shouldSkip:" << shouldSkip;
                    }

                    if (bDebug)  qDebug() << "imgsrc:" << imgsrc;
                    ans += imgsrc;
                    canTry = false;
                    break;
                } else {
                    canTry = true;
                    foo = tmp;
                }

                if (!sl.isEmpty()) {
                    tmp = foo + QString("-") +  sl.takeFirst();
                    //qDebug() << "87: tmp:" << tmp;
                    re = QRegularExpression(tmp);
                    matchList.clear();
                    canTry = true;
                } else {
                    canTry = false;
                }
            }
        } while (canTry);
    }

    qDebug() << "ans:" << ans;
    return ans;
}

QStringList EmojiCore::string_to_codepoint_list(const QString& s)
{
    QStringList sl;
    int p = 0;
    while (p < s.count()) {
        QChar cc = s[p];

        if (cc.isHighSurrogate()) {
            //qDebug() << cc << "isHighSurrogate";
            p ++;
            QChar dd = s[p];
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
    return sl;
}

void EmojiCore::test0()
{
    qDebug() << __func__;
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

    QStringList sl = string_to_codepoint_list(QString::fromUtf8((const char*)buf));
    qDebug() << "sl:" << sl;
    setSequence(parse_codepoint_list(sl));
}

void EmojiCore::test1()
{
    qDebug() << __func__;
    QStringList sl = {
        "1f1e7", "1f1ff", "1f365", "39", "20e3", "26f9", "fe0f",
        "200d", "2642", "fe0f", "26bd", "23", "20e3",
    };
    qDebug() << "sl:" << sl;
    parse_codepoint_list(sl);
}
