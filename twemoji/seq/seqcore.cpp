#include "seqcore.h"

#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

#include <QFile>
#include <QHash>
#include <QRegularExpression>
#include <QDebug>


SeqCore* SeqCore::_instance = nullptr;
SeqCore* SeqCore::getInstance()
{
    if (_instance == nullptr) {
        _instance = new SeqCore();
    }
    return _instance;
}


SeqCore::SeqCore(QObject *_parent) : QObject(_parent)
{
    //qDebug() << __func__;
    load_seq();
}

// load seq.json from resource, and keep it in ba_buffer
void SeqCore::load_from_res()
{
    QFile file(":/seq.json");
    file.open(QIODevice::ReadOnly);
    ba_buffer = file.readAll();
}

void SeqCore::load_seq()
{
    using namespace std;
    using namespace nlohmann;

    int cnt = 0;

    load_from_res();
    try {
        json j = json::parse(ba_buffer.data());

        for (json::iterator it = j.begin(); it != j.end(); ++it) {
            QString key;
            QStringList val_list;

            key = QString::fromStdString(it.key());
            //cout << it.key() << "\t";
            cnt ++;
            QList<QStringList> ll;
            for (json::iterator jt = (*it).begin(); jt != (*it).end(); ++jt) {
                QStringList slist;
                for (json::iterator kt = (*jt).begin(); kt != (*jt).end(); ++kt) {
                    slist << QString::fromStdString((*kt));
                }
                ll.append(slist);
            }
            qq[key] = ll;
        }
    } catch (json::parse_error& e) {
        cout << "parse error:" << e.what() << endl;
    }

    key_count = cnt;
    cout << "key count: " << cnt << endl;
}


bool SeqCore::lookup_list(const QStringList& t)
{
    if (t.isEmpty()) {
        return false;
    }
    //qDebug() << "lookup_list, t:" << t;
    QString k = t[0];
    bool found = false;
    if (qq.contains(k)) {
        QList<QStringList> ql = qq.value(k);
        for (int i=0; i<ql.size(); i++) {
            if (t.size() != ql.at(i).size()) {
                continue;
            }
            //qDebug() << "-----" << t << "vs" << ql.at(i);
            if (t == ql.at(i)) {
                found = true;
                //qDebug() << "found:" << t;
                break;
            }
        }
    }

    if (found) {
        add_to_answer(t);
    }
    return found;
}


bool SeqCore::get_possible_len(const QStringList& t, QList<int>& pls)
{
    if (t.isEmpty()) {
        return false;
    }

    QString k = t[0];
    QHash<int, int> possible_lens;
    if (qq.contains(k)) {
        QList<QStringList> ql = qq.value(k);
        for (int i=0; i<ql.size(); i++) {
            int sz = ql.at(i).size();
            possible_lens[sz] ++;
        }
    }
    pls = possible_lens.keys();
    std::sort(pls.begin(), pls.end());
    //qDebug() << "possible length:" << pls;
    return true;
}

bool SeqCore::get_possible_len(const QString& k, QList<int>& pls)
{
    if (k.isEmpty()) {
        return false;
    }
    struct {
        bool operator()(int a, int b) const {
            return a > b;
        }
    } customLess;

    QHash<int, int> possible_lens;
    if (qq.contains(k)) {
        QList<QStringList> ql = qq.value(k);
        for (int i=0; i<ql.size(); i++) {
            int sz = ql.at(i).size();
            possible_lens[sz] ++;
        }
    }
    pls = possible_lens.keys();
    std::sort(pls.begin(), pls.end(), customLess);
    //qDebug() << "possible length:" << pls;
    return true;
}

QStringList SeqCore::get_trylist(const QStringList& t, int try_len)
{
    if (try_len > t.size()) {
        qDebug() << "[FAIL] fetch too long";
        return QStringList();
    }
    QStringList try_list;
    for (int i=0; i<try_len; i++) {
        try_list << t[i];
    }
    return try_list;
}

bool SeqCore::match(const QStringList& tl)
{
    if (!tl.isEmpty()) {
        if (lookup_list(tl)) {
            return true;
        }
    }

    return false;
}

void SeqCore::add_to_answer(const QStringList& sl)
{
    if (isDebug)
        qDebug() << __func__ << ":" << sl;
    QString s = sl.join("-");
    QString imgsrc = QString(
        "<img height=\"32\" width=\"32\"src=\"72x72/%1.png\">").arg(s);
    if (isDebug)
        qDebug() << "[INFO] imgsrc:" << imgsrc;
    emoji_ans += imgsrc;
}

void SeqCore::pop_to_answer(const QString& ch)
{
    if (ch.isEmpty() || ch == "fe0f") {
        // skip
        return;
    }
    bool ok;
    int v = ch.toInt(&ok, 16);
    QString ret = QString(QChar(v));
    if (isDebug)
        qDebug() << "pop char:" << ret;
    emoji_ans += ret;
}

void SeqCore::setCodepointSequence(const QStringList& tl)
{
    if (!key_count) {
        qDebug() << "[FAIL] no sequence data";
        return;
    }
    if (!emoji_ans.isEmpty()) {
        emoji_ans = "";
    }

    QStringList t = tl;
    QStringList ans;
    while (!t.isEmpty()) {
        if (isDebug)
            qDebug() << "=======" << t << "=======";
        QString cc = t.first();
        if (isDebug)
            qDebug() << "cc:" << cc;
        QList<int> pls;
        get_possible_len(cc, pls);
        //qDebug() << "pls:" << pls;
        if (pls.isEmpty()) {
            pop_to_answer(t.takeFirst());
            continue;
        }
        bool matched = false;
        for (int ii=0; ii<pls.size(); ii++) {
            int max_try_len = pls.at(ii);
            //qDebug() << "max_try_len:" << max_try_len;
            QStringList try_list;

            for (int i=max_try_len; i>0; i--) {
                if (i > t.size()) {
                    continue;
                }
                try_list = get_trylist(t, i);
                if (isDebug)
                    qDebug() << "try this:" << try_list;
                if (match(try_list)) {
                    for (int zz=0; zz<i; zz++) {
                        t.takeFirst();
                        //qDebug() << "now t:" << t;
                    }
                    matched = true;
                    break;
                } else {
                    matched = false;
                }
            }
            if (!matched) {
                pop_to_answer(t.takeFirst());
            }
            break;
        }
    }

    qDebug() << "[INFO] ans:" << emoji_ans;
}

void SeqCore::test()
{
    qDebug() << __func__;

    QStringList t = {
        //"39", "1f3c3","1f3fb","200d","2640","fe0f", "53"
        "33", "33", "20e3", "2a", "20e3", "26f9", "1f3fb", "200d", "2640", "fe0f"
        //"1f9cf", "1f9cf", "1f3fd", "1f9cf", "1f3fc", "200d", "2642", "fe0f"
        //"270c", "1f3fe", "270b", "2728", "1f9e3", "1f9dd", "1f3fe", "200d", "2640", "fe0f"
        //"2764", "fe0f", "1f1e7", "1f1f4", "1f64b", "200d", "2640", "fe0f", "1f3c8", "1f603"
    };
    setCodepointSequence(t);
}
