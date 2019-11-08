
#include "testcases.h"

#include <QRegularExpression>

#include <sys/file.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void localre(const QString& re, const QString& str)
{
    QRegularExpression regexp(re);
    QRegularExpressionMatch match = regexp.match(str);
    if (match.hasMatch()) {
        qDebug() << Q_FUNC_INFO << match.captured(1);
    } else {
        qDebug() << Q_FUNC_INFO << "no matched";
    }
}

void testSizeOfDataType()
{
    qDebug() << QString("ulonglong = %1, "
        "ulong = %2, ushort = %3, "
        "quint64 = %4, quint32 = %5, quint16 = %6")
        .arg(QString::number(sizeof(unsigned long long)))
        .arg(QString::number(sizeof(unsigned long)))
        .arg(QString::number(sizeof(unsigned short)))
        .arg(QString::number(sizeof(quint64)))
        .arg(QString::number(sizeof(quint32)))
        .arg(QString::number(sizeof(quint16)));
}

void dump_hash(const QHash<QString, QString>& hh)
{
    qDebug() << "    hash {";
    QHash<QString, QString>::const_iterator it;
    for (it = hh.cbegin(); it != hh.cend(); ++it) {
        qDebug() << "        " << it.key() << ":" << it.value();
    }
    qDebug() << "    } hash end;";

    // QHash<QObject *, int>::iterator i = objectHash.find(obj);
    // while (i != objectHash.end() && i.key() == obj) {
    //     if (i.value() == 0) {
    //         i = objectHash.erase(i);
    //     } else {
    //         ++i;
    //     }
    // }

}

enum CommandParsingResultType {
    kError = 17389,
    kNoPair = 37813,
    kWithPair = 59359,
    kUnknown = 1299709
};

CommandParsingResultType extractKeyValuePair(const QString& str,
    QHash<QString, QString>& pairs, QString& left_part)
{
    pairs.clear();
    left_part = "";
    if (str.isEmpty()) {
        return kError;
    }

    QRegularExpression re("(?<key>[A-Za-z][A-Za-z0-9_]*)\\s*=\\s*(?<val>[^/]+)");
    QString s = str;
    //qDebug() << "test on" << s << "==========<<";
    QRegularExpressionMatchIterator i = re.globalMatch(s);
    int early = s.size();
    int last = -1;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        int start = match.capturedStart();
        int end = match.capturedEnd();
        early = (start < early) ? start : early;
        last = (end > last) ? end : last;
        // qDebug() << "start:" << start << ","
        //          << "end:" << end
        //          << "mid:" << s.mid(start, end-start+1);
        QString key = match.captured("key");
        QString val = match.captured("val");
        //qDebug() << "match: " << key << "=" << val;
        pairs.insert(key, val);
    }
    if (!pairs.size()) {
        left_part = str;
        return kNoPair;
    }
    //qDebug() << "last:" << last << "," << "early:" << early;
    if (last > early) {
        //qDebug() << "captured group:" << s.mid(early, last - early + 1);
        //qDebug() << "left part:" << s.left(early);
        left_part = s.left(early);
        return kWithPair;
    }

    return kUnknown;
}

void testRegexp2()
{
    QStringList sl = {
        "calleventshow/on",
        //"calleventshow/on/",
        "calleventshow/on/debug=xxx",
        //"calleventshow/on/debug=xxx/whatthefuck",
        "calleventshow/on/debug=xxx/whatthefuck/",
        "calleventshow/on/caller=svc_hmi_yyy",
        "calleventshow/on/caller=svc_hmi_yyy/debug=ipodui",
        "calleventshow/on/debug=xxx/caller=svc_hmi_yyy",
        //"json/[\"title/Home/debug=cli\",\"showbutton/off/debug=testopt\","
        //"\"showback/on/debug=foobar\"]"
    };
    QHash<QString, QString> pairs;
    CommandParsingResultType ret;
    QString left_part;
    foreach (QString s, sl) {
        ret = extractKeyValuePair(s, pairs, left_part);
        qDebug() << "ret:" << ret << "s:" << s;
        dump_hash(pairs);
        qDebug() << left_part;
    }
}

int removeTrailSlash(const QString& str, QString& out)
{
    out = str;
    QRegularExpression re("/$");
    QRegularExpressionMatch m = re.match(str);
    //int start = m.capturedStart();
    //int end = m.capturedEnd();
    int len = m.capturedLength();
    //qDebug() << "len:" << len << "start:" << start << "end:" << end;
    if (len) {
        out.chop(len);
    }
    return 0;
}


void testRegexp()
{
    QStringList sl = {
        "calleventshow/on",
        "calleventshow/on/",
    };

    QString out;
    foreach (QString s, sl) {
        removeTrailSlash(s, out);
        qDebug() << "out:" << out;
    }
}


/*
RF,Kpa,230,C,30,OK*4F
RR,Kpa,230,C,30,OK*4F
LR,Kpa,230,C,30,OK*4F
LF,Kpa,230,C,30,OK*4F
*/
void testParseTPMS()
{
    QRegularExpression re("(?<pos>[LR][RF]),"
                          "(?<punit>(Kpa|Psi|Bar)),"
                          "(?<press>\\d+\\.?\\d*),"
                          "(?<tunit>(C|F)),"
                          "(?<temp>\\d+),"
                          "(?<batt>(OK|LOW))");
    QString s = "RF,Kpa,230,C,30,OK*4F";
    QRegularExpressionMatch match = re.match(s);
    if (match.hasMatch()) {
        QString pos = match.captured("pos");
        QString punit = match.captured("punit");
        QString press = match.captured("press");
        QString tunit = match.captured("tunit");
        QString temp = match.captured("temp");
        QString batt = match.captured("batt");
        qDebug() << pos << punit << press << tunit << temp << batt;
    }
}

/// https://en.wikipedia.org/wiki/Percent-encoding
void testPercentEncoding()
{
    QString s = "I%60m Lengend%21";
    QRegularExpression re("(%([A-Fa-f0-9][A-Fa-f0-9]))");
    QRegularExpressionMatchIterator i = re.globalMatch(s);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString all = match.captured(1);
        QString key = match.captured(2);
        bool ok;
        int _hex = key.toInt(&ok, 16);
        if (ok) {
            char value = (char)_hex;
            QString after = QString(value);
            qDebug() << "all:" << all << "key:" << key << ":" << after;
            s.replace(all, after);
            qDebug() << "s:" << s;
        }
    }
}

QString translate_utf16be_to_qstring(const unsigned char utf16be[32])
{
    const int MAXLEN = 32;
    QString str = "";
    for (int i = 0; i < MAXLEN/2; i+=2) {
        //printf("i: %02x %02x\n", utf16be[i], utf16be[i+1]);
        ushort uc = (utf16be[i] << 8) | utf16be[i+1];
        if (uc == 0) {
            break;
        }
        //printf("uc: %04x\n", uc);
        QChar cc = QChar(uc);
        //qDebug() << cc;
        str = str + QString(cc);
    }

    //qDebug() << "str:" << str;
    return str;
}


void testParseSysinfo()
{
    char s[] =
"system: CIS002-0.01.001.201609082206\x0a"
"uboot: 40\x0a"
"mcu:201608030004\x0a"
"lcd:201609130008\x0a"
"board id:2\x0a";

    localre("system: ([A-Za-z0-9.-]+)", s);
    localre("uboot: ([A-Za-z0-9.-]+)", s);
    localre("mcu:([A-Za-z0-9.-]+)", s);
    localre("lcd:([A-Za-z0-9.-]+)", s);
    localre("board id:([A-Za-z0-9.-]+)", s);
    // QString _sysinfo;
    // QRegularExpression re("system: (?<sys>[A-Za-z0-9.-]+)");
    // QRegularExpressionMatch match = re.match(s);
    // if (match.hasMatch()) {
    //     _sysinfo = match.captured("sys");
    //     qDebug() << Q_FUNC_INFO << _sysinfo;
    // } else {
    //     qDebug() << Q_FUNC_INFO << "no matched";
    // }

    // QRegularExpression re2("uboot: ([A-Za-z0-9.-]+)");
    // QRegularExpressionMatch match = re2.match(s);
    // if (match.hasMatch()) {
    //     qDebug() << match.captured(1);
    // }

}

#define DO_TEST(x) \
    qDebug() << x << "?" << (isInBlackList(x) ? "yes" : "no")

void testblacklist()
{
    DO_TEST("currentTime");
    DO_TEST("tomorrowTime");
    DO_TEST("language");
    DO_TEST("Language");
    DO_TEST("prayTime");
    DO_TEST("cautionAutodismiss");
}

bool isInBlackList(const QString& prop)
{
    if (prop == "currentTime") {
        return true;
    } else if (prop == "language") {
        return true;
    } else if (prop == "prayTime") {
        return true;
    } else if (prop == "cautionAutodismiss") {
        return true;
    }

    return false;
}

void testqurl()
{
#define TESTFILE "/tmp/A good book! #hash this!.mp3"
    QUrl foo = QUrl::fromLocalFile(TESTFILE);
    qDebug() << foo << "," << foo.toString();
}
