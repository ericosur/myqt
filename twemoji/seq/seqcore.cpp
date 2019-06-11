#include "seqcore.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>

#include <QMap>
#include <QHash>
#include <QString>
#include <QRegularExpression>
#include <QByteArray>
#include <QThread>
#include <QDebug>


SeqCore* SeqCore::_instance = NULL;
SeqCore* SeqCore::getInstance()
{
    if (_instance == NULL) {
        _instance = new SeqCore();
    }
    return _instance;
}


SeqCore::SeqCore(QObject *_parent) : QObject(_parent)
{
    //qDebug() << __func__;
    load_seq();
}

void SeqCore::load_seq()
{
    using namespace std;
    using namespace nlohmann;
    string json_file = "../seq.json";
    int cnt = 0;

    try {
        ifstream inf(json_file);
        json j;
        inf >> j;

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

    cout << "key count: " << cnt << endl;
}


bool SeqCore::lookup_list(const QStringList& t, QString& ans)
{
    if (t.isEmpty()) {
        return false;
    }
    qDebug() << "lookup_list, t:" << t;
    ans = "";
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
                qDebug() << "found:" << t;
                break;
            }
        }
    }
    if (found) {
        ans = t.join("-");
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
    if (tl.isEmpty()) {
        return false;
    }

    QString ans;
    if (lookup_list(tl, ans)) {
        qDebug() << "ans:" << ans;
        return true;
    }

    return false;
}

void SeqCore::pop(const QString& s)
{
    if (s == "fe0f") {
        // skip
        return;
    }
    qDebug() << "pop:" << s;
}

void SeqCore::travel_sequence(const QStringList& tl)
{
    QStringList t = tl;
    QStringList ans;
    while (!t.isEmpty()) {
        qDebug() << "==========" << t << "==========";
        QString cc = t.first();
        qDebug() << "cc:" << cc;
        QList<int> pls;
        get_possible_len(cc, pls);
        //qDebug() << "pls:" << pls;
        if (pls.isEmpty()) {
            pop(t.takeFirst());
            continue;
        }
        bool matched = false;
        for (int ii=0; ii<pls.size(); ii++) {
            int max_try_len = pls.at(ii);
            //qDebug() << "max_try_len:" << max_try_len;
            QStringList try_list;
            //bool tryNext = true;

            for (int i=max_try_len; i>0; i--) {
                if (i > t.size()) {
                    continue;
                }
                try_list = get_trylist(t, i);
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
                pop(t.takeFirst());
            }
            break;
        }
    }
}

void SeqCore::test()
{
    qDebug() << __func__;

    QStringList t = {
        //"39", "1f3c3","1f3fb","200d","2640","fe0f", "53"
        //"33", "33", "20e3", "2a", "20e3", "26f9", "1f3fb", "200d", "2640", "fe0f"
        //"1f9cf", "1f9cf", "1f3fd", "1f9cf", "1f3fc", "200d", "2642", "fe0f"
        //"270c", "1f3fe", "270b", "2728", "1f9e3", "1f9dd", "1f3fe", "200d", "2640", "fe0f"
        "2764", "fe0f", "1f1e7", "1f1f4", "1f64b", "200d", "2640", "fe0f", "1f3c8", "1f603"
    };
    travel_sequence(t);

}
