#ifndef __DEVINFO_H__
#define __DEVINFO_H__

#include <QObject>
#include <QString>

#ifdef USE_YOSETARGET
// default LCD dimension
#define DEFAULT_F_HEIGHT    "800"
#define DEFAULT_F_WIDTH     "1280"
#else
#define DEFAULT_F_HEIGHT    "900"
#define DEFAULT_F_WIDTH     "1440"
#endif

class DeviceScreen
{
public:
    DeviceScreen();
    ~DeviceScreen() {}

    QString getFrontWidth();
    QString getFrontHeight();
    QString getInfostring(int startx=0, int starty=0);

protected:
    QString get_env(const QString& key, const QString& default_value) const;

private:
    QString mWidth = DEFAULT_F_WIDTH;
    QString mHeight = DEFAULT_F_HEIGHT;
};

void test_deviceinfo();

#endif // __DEVINFO_H__
