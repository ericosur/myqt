#include "testz.h"

#include <QTimeZone>
#include <QString>
#include <QDebug>

void test_timezone()
{
    qDebug() << Q_FUNC_INFO << QTimeZone::systemTimeZoneId();
}
