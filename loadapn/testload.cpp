#include "testload.h"

#include <QDateTime>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QMap>

#include <QDebug>

Solution::Solution()
{
    re.setPattern("(?<key>[A-Z]+)=(?<val>([^;]+)?);");
    re.optimize();

    load_apn1_file();
}

Solution::~Solution()
{
    apn1File.close();
}

void Solution::loadApnDatabase_old()
{
    qInfo() << __func__;
    QString path = ":/apn0.txt";

    QFile apnFile(path);
    if (!apnFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Gemalto/Modem: open apn file fail" << path;
        return;
    }

    QTextStream in(&apnFile);
    QString line;
    QStringList list;

    QMap<QString, QString> collectData;
    QString imsi;
    while (!in.atEnd()) {
        line = in.readLine();

        if (line.contains("BEGIN:APN")) {
            collectData.insert("imsi", "");
            collectData.insert("apn","");
            collectData.insert("username","");
            collectData.insert("password","");
        }
        if (line.contains("APNNAME")) {
            list = line.split("=");
            collectData.insert("apn",list[1]);
        }
        if (line.contains("IMSI")) {
            list = line.split("=");
            collectData.insert("imsi", list[1]);
        }
        if (line.contains("USERNAME")) {
            list = line.split("=");
            collectData.insert("username",list[1]);
        }
        if (line.contains("PASSWORD")) {
            list = line.split("=");
            collectData.insert("password",list[1]);
        }
        if (line.contains("END:APN")) {
            //qDebug() << "Gemalto/Modem: apn list:" << collectData;
            apnList0.append(collectData);
        }
    }

    apnFile.close();
}

void Solution::loadApnDatabase_new()
{
    qInfo() << __func__;

    textStream.setDevice(&apn1File);
    textStream.seek(0);

    QString line;
    QString item;
    QStringList list;
    QStringList info;

    QMap<QString, QString> collectData;
    while (!textStream.atEnd()) {
        line = textStream.readLine();
        if (line.contains("BEGIN:APN") && line.contains("END:APN")) {
            collectData.insert("imsi", "");
            collectData.insert("apn", "");
            collectData.insert("username", "");
            collectData.insert("password", "");
            list = line.split(";");
            for (int i = 0; i < list.size(); i++) {
                item = list.at(i);
                if (item.contains("APNNAME")) {
                    info = item.split("=");
                    collectData.insert("apn", info.at(1));
                }
                if (item.contains("IMSI")) {
                    info = item.split("=");
                    collectData.insert("imsi", info.at(1));
                }
                if (item.contains("USERNAME")) {
                    info = item.split("=");
                    collectData.insert("username", info.at(1));
                }
                if (item.contains("PASSWORD")) {
                    info = item.split("=");
                    collectData.insert("password", info.at(1));
                }
            }
            //qDebug() << "Gemalto/Modem: apn list:" << collectData;
            apnList1.append(collectData);
        }
    }
}

void Solution::test_parse()
{
    QMap<QString, QString> res;
    res = parse_line("BEGIN:APN;APNNAME=etisalat.ae;IMSI=42402;USERNAME=;PASSWORD=;END:APN");
    qDebug() << res;
}

void Solution::load_apn1_file()
{
    apn1File.setFileName(":/apn1.txt");
    if (!apn1File.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "[ERROR] open apn1 file fail...";
    }
}

/// BEGIN:APN;APNNAME=etisalat.ae;IMSI=42402;USERNAME=;PASSWORD=;END:APN
QMap<QString, QString> Solution::parse_line(const QString& line)
{
    //qDebug() << "got:" << line;
    QMap<QString, QString> collectData;
    QRegularExpressionMatchIterator i = re.globalMatch(line);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString key = match.captured("key");
        QString val = match.captured("val");
        collectData.insert(key, val);
        //qDebug() << "match: " << key << "=" << val;
    }
    return collectData;
}


void Solution::load_apn_re()
{
    qInfo() << __func__;

    textStream.setDevice(&apn1File);
    textStream.seek(0);

    QMap<QString, QString> collectData;
    while (!textStream.atEnd()) {
        QString line = textStream.readLine();
        collectData = parse_line(line);
        if (collectData.size()) {
            apnList2.append(collectData);
        }
    }
}


void test_load()
{
    qDebug() << __func__;
    Solution foo;

    qint64 start;
    qint64 end;

    start = QDateTime::currentMSecsSinceEpoch();
    foo.loadApnDatabase_old();
    end = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "len apn0:" << foo.apnList0.length();
    qDebug() << "epoch:" << end - start;

    start = QDateTime::currentMSecsSinceEpoch();
    foo.loadApnDatabase_new();
    end = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "len apn1:" << foo.apnList1.length();
    qDebug() << "epoch:" << end - start;

    start = QDateTime::currentMSecsSinceEpoch();
    foo.load_apn_re();
    end = QDateTime::currentMSecsSinceEpoch();
    qDebug() << "len apn2:" << foo.apnList2.length();
    qDebug() << "epoch:" << end - start;


}
