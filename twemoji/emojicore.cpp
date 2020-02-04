#include "emojicore.h"
#include "seq/seqcore.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <QThread>
#include <QDebug>

EmojiCore* EmojiCore::_instance = nullptr;

EmojiCore* EmojiCore::getInstance()
{
    if (_instance == nullptr) {
        _instance = new EmojiCore();
    }
    return _instance;
}


EmojiCore::EmojiCore(QObject *_parent) : QObject(_parent)
{
    //test0();
    //test1();

    load_tests();

    connect(this, SIGNAL(countChanged()), this, SLOT(sltCountChanged()));
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

void EmojiCore::runTest(const QStringList& sl)
{
    SeqCore* seq = SeqCore::getInstance();
    seq->setCodepointSequence(sl);
    QString ret = seq->getEmojiSequence();
    setSequence(ret);
}


void EmojiCore::sltCountChanged()
{
    //qDebug() << __func__;

    if (!test_list.isEmpty()) {
        list_idx = (mCount % test_list.size());

        QString fromStr = test_list[list_idx];
        setInstr(fromStr);
        QStringList sl = string_to_codepoint_list(fromStr);
        runTest(sl);
        qDebug() << "====================";
    }
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
    runTest(sl);
}

void EmojiCore::test1()
{
    qDebug() << __func__;
    QStringList sl = {
        "1f1e7", "1f1ff", "1f365", "39", "20e3", "26f9", "fe0f",
        "200d", "2642", "fe0f", "26bd", "23", "20e3",
    };
    qDebug() << "sl:" << sl;
    runTest(sl);
}
