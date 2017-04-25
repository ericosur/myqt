#include "devinfo.h"

DeviceScreen::DeviceScreen()
{
    mWidth = get_env("FRONT_W", DEFAULT_F_WIDTH);
    mHeight = get_env("FRONT_H", DEFAULT_F_HEIGHT);
}

QString DeviceScreen::get_env(const QString& key, const QString& default_value) const
{
    QString _str = qgetenv(key.toUtf8().data());

    // if empty
    if (_str.isEmpty()) {
        return default_value;
    }

    // if not a number or too small
    bool ok = false;
    int val = _str.toInt(&ok);
    // check if a valid number
    if (!ok || val <= 0) {
        return default_value;
    }

    return _str;
}

QString DeviceScreen::getFrontWidth()
{
    return mWidth;
}

QString DeviceScreen::getFrontHeight()
{
    return mHeight;
}

QString DeviceScreen::getInfostring(int startx, int starty)
{
    QString str = QString("pos_f={%1,%2,%3,%4}")
        .arg(startx).arg(starty)
        .arg(mWidth).arg(mHeight);

    //qDebug() << "getInfostring: str:" << str;

    return str;
}
