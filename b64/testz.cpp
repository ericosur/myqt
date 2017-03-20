#include "testz.h"

#include <QList>
#include <QByteArray>
#include <QTimeZone>
#include <QString>
#include <QDebug>

void test_timezone()
{
    qDebug() << Q_FUNC_INFO << QTimeZone::systemTimeZoneId();

    QList<QByteArray> array = QTimeZone::availableTimeZoneIds();
    foreach (QByteArray aa, array) {
        qDebug() << aa;
    }
}
