#include "emojicore.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <QString>
#include <QRegularExpression>
#include <QByteArray>
#include <QThread>
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
    connect(test_timer, SIGNAL(timeout()), this, SLOT(sltTimeout()), Qt::DirectConnection);
    test_timer->setSingleShot(true);
    test_timer->setInterval(1000);
    test_timer->start();

    //test0();
}

void EmojiCore::load_tests()
{
    using namespace std;
    using namespace nlohmann;
    string json_file = "../test.json";
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
        QStringList sl = string_to_codepoint_list(test_list[list_idx++]);
        //QStringList sl = string_to_codepoint_list(test_list[i]);
        QString ans = parse_codepoint_list(sl);
        qDebug() << ans;
        setSequence(ans);
        list_idx = list_idx % test_list.size();
        qDebug() << "====================";
    }
    test_timer->setSingleShot(true);
    test_timer->start();
}

QString EmojiCore::fetch_tail_part(const QString& str)
{
    int idx = str.indexOf('-');
    QString rhs = "null";
    if (idx >= 0) {
        rhs = str.right(str.size()-1-idx);
    }
    //qDebug() << "rhs:" << rhs;
    return rhs;
}

kEmojiType EmojiCore::pop_str_codepoint(const QString& cp, QString& ret)
{
    ret = "";
    if (cp.isEmpty() || cp == "fe0f") {
        return EmojiInvalid;
    }
    bool ok;
    int v = cp.toInt(&ok, 16);
    if (v == 0xa9 || v == 0xae || v >= 0x1f000) {
        ret = compose_imgsrc(cp);
        //qDebug() << "pop_str_codepoint: imgsrc:" << ret;
        return EmojiImage;
    } else if (v == 0x23 || v == 0x2a || (v >= 0x30 && v <= 0x39)) {
        return EmojiNeedNextChar20e3;
    }

    ret = QString(QChar(v));
    qDebug() << "pop char:" << ret;
    return EmojiNone;
}

QString EmojiCore::compose_imgsrc(const QString& s)
{
    QString imgsrc = QString(
        "<img height=\"28\" width=\"28\"src=\"72x72/%1.png\">").arg(s);
    return imgsrc;
}

QString EmojiCore::pop_one_codepoint(const QString& cp)
{
    bool ok;
    int v = cp.toInt(&ok, 16);
    return QString(QChar(v));
}


// NOTE: if pop char is U+FE0F, should drop it
QString EmojiCore::parse_codepoint_list(const QStringList& strlist)
{
    qDebug() << __func__ << "input sl:" << strlist;
    QStringList sl = strlist;
    QRegularExpression re;
    QString foo;
    bool canTry = false;
    QString shouldSkip;
    QString ans;
    bool bDebug = true;

    // takeFirst
    while (!sl.isEmpty()) {
        foo = "";

        QString cc = sl.takeFirst();
        //if (bDebug)  qDebug() << "curr:" << cc;
        if (cc == shouldSkip) {
            qDebug() << "skip this cc," << cc;
            shouldSkip = "";
            continue;
        }

        // direct add into ans
        QString rrt;
        {
            kEmojiType t = pop_str_codepoint(cc, rrt);
            if (t == EmojiNone) {
                ans += rrt;
                continue;
            } else if (t == EmojiNeedNextChar20e3 && !sl.isEmpty()) {
                QString next_char = sl.first();
                if (next_char == "20e3") {
                    ans += compose_imgsrc(cc + "-20e3");
                    sl.removeFirst();
                } else {
                    ans += pop_one_codepoint(cc);
                }
                continue;
            } else if (t == EmojiNeedNextChar1f3xx && !sl.isEmpty()) {
                QString next_char = sl.first();
                if (next_char.contains(QRegularExpression("^1f3f[bcdef]"))) {
                    ans += compose_imgsrc(cc + "-" + next_char);
                    sl.removeFirst();
                } else {
                    ans += pop_one_codepoint(cc);
                }
            }
        }

        QString tmp = QString("^") + cc;
        re = QRegularExpression(tmp);

        do {
            //if (bDebug)  qDebug() << "try re =====> " << re.pattern();
            QStringList matchList = emojiList.filter(re);
            //if (bDebug)  qDebug() << "matchList ===>" << matchList;
            if (matchList.isEmpty()) {
                ans += pop_str_codepoint(cc, rrt);
                canTry = false;
                break;
            }
            // matchList is not empty
            qDebug() << "matched:" << matchList;
            QStringList tail_list;

            if (matchList.size() == 1) {
                QString t = matchList[0];
                QString imgsrc = compose_imgsrc(t);
                //qDebug() << "matched img:" << t;

                int idx = t.lastIndexOf("-");
                if (idx != -1) {
                    shouldSkip = t.right(t.size()-idx-1);
                    if (bDebug)  qDebug() << "shouldSkip:" << shouldSkip;
                }

                //if (bDebug)  qDebug() << "imgsrc:" << imgsrc;
                ans += imgsrc;
                canTry = false;
                break;
            }

            // matched multiple possible emoji images
            canTry = true;
            foo = tmp;
            for (QString s: matchList) {
                tail_list << fetch_tail_part(s);
            }

            if (!sl.isEmpty()) {
                QString pre_fetched_first = sl.first();
                if (!tail_list.contains(pre_fetched_first)) {
                    if (tail_list.contains("null")) {
                        // pop current matched char, and pre_fetched_first
                        //qDebug() << "pop cc:" << cc;
                        //QString imgsrc = compose_imgsrc(cc);
                        pop_str_codepoint(cc, rrt);
                        ans += rrt;
                        //qDebug() << "also pop:" << pre_fetched_first;
                        pop_str_codepoint(pre_fetched_first, rrt);
                        ans += rrt;
                        sl.removeFirst();
                        canTry = false;
                    }
                } else {
                    tmp = foo + QString("-") +  sl.takeFirst();
                    //qDebug() << "87: tmp:" << tmp;
                    re = QRegularExpression(tmp);
                    matchList.clear();
                    canTry = true;
                }
            } else {
                canTry = false;
            }
        } while (canTry);
    }

    //qDebug() << "ans:" << ans;
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
