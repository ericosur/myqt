#include "testz.h"
#include "gettz.h"

#include <QList>
#include <QLocale>
#include <QTimeZone>
#include <QDateTime>
#include <QString>
#include <QByteArray>
#include <QDebug>

void test_timezone()
{
    qDebug() << Q_FUNC_INFO << "from qt:" << QTimeZone::systemTimeZoneId() << Qt::endl
        << "getTimeZoneNameFromLink()" << getTimeZoneNameFromLink();


#if 0
    QList<QByteArray> array = QTimeZone::availableTimeZoneIds();
    foreach (QByteArray aa, array) {
        qDebug() << aa;
    }
#endif
}

void test_locale()
{
    // ar_AE
    QLocale arae(QLocale::Arabic, QLocale::UnitedArabEmirates);
    double n1 = 1.571429E+07;
    int n2 = 10;
    QString s1 = arae.toString(n1, 'e');
    QString s2 = arae.toString(n2);

    // double d = arae.toDouble(s1);
    // int i = arae.toInt(s2);
    qDebug() << "arae:" << arae;
    qDebug() << n1 << "==>" << s1 << Qt::endl
        << n2 << "==>" << s2;

    QDateTime now = QDateTime::currentDateTime();
    qDebug() << now << "==>" << arae.toString(now);
}
