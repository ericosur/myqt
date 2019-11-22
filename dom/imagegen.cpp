#include "imagegen.h"

#include <QStringList>
#include <QPainter>
#include <QJsonArray>
#include <QDebug>
#include <math.h>

const float PI = 3.1415926535897932384626433832795028841972;

inline float deg2rad(float deg) {
    return deg * PI / 180.0;
}
inline float circle_x(float x, float r, float deg) {
    float p = x + r * cos(deg2rad(deg));
    return p;
}
inline float circle_y(float y, float r, float deg) {
    float p = y + r * sin(deg2rad(deg));
    return p;
}
inline int navi2arc(int d) {
    int arc = 90;
    if (d < 0 && d >= -360) {
        arc = -d + 90;
    } else if (d >= 0 && d <= 90) {
        arc = abs(d - 90);
    } else if (d > 90 && d <= 360) {
        arc = 360 - (d - 90);
    }
    return arc;
}
inline void swap(int& m, int& n)
{
    int t = m;
    m = n;
    n = t;
}
inline int navi2exit(int d) {
    int a = 0;
    if (d >= 90 && d <= 180) {
        a = d - 90;
    } else if (d >= 0 && d < 90) {
        a = d + 270;
    } else if (d < 0 && d >= -90) {
        a = 270 + d;
    } else if (d < -90 && d >= -180) {
        a = 270 + d;
    }
    return a;
}
ImageGen* ImageGen::_instance = nullptr;
ImageGen* ImageGen::getInstance()
{
    if (_instance == nullptr) {
        _instance = new ImageGen();
    }
    return _instance;
}

ImageGen::ImageGen()
{
}

bool ImageGen::draw_png(const QString& ofn)
{
    qDebug() << "draw_png:" << ofn;

    const int DEFAULT_WIDTH = 400;
    const int DEFAULT_HEIGHT = 400;
    bool drivingRight = true;
    int arcBegin = 0;
    int arcEnd = 0;
    int arcSpan = 0;
    int arcPadding = 0;
    int jExitAngle = _jo["junctionElementExitAngle"].toInt();

    if (_jo["drivingSide"].toString() == "left") {
        drivingRight = false;
    }
    if (drivingRight) {
        arcBegin = 270;
        arcEnd = navi2arc(jExitAngle);
        if (jExitAngle >= 0 && jExitAngle <= 180) {
            arcSpan = abs(jExitAngle - 180) - arcPadding;
        } else if (jExitAngle < 0 && jExitAngle >= -180) {
            arcSpan = abs(jExitAngle) + 180 - arcPadding;
        }
    } else {
        arcBegin = navi2arc(jExitAngle);
        arcEnd = 270;
        if (jExitAngle >= 0 && jExitAngle <= 180) {
            arcSpan = jExitAngle + 180 + arcPadding;
        } else if (jExitAngle < 0 && jExitAngle >= -180) {
            arcSpan = 180 + jExitAngle + arcPadding;
        }
    }
    // if (arcEnd < arcBegin) {
    //     swap(arcBegin, arcEnd);
    // }
    qDebug() << "arcBegin:" << arcBegin;
    qDebug() << "arcEnd:" << arcEnd;
    QImage image(QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT), QImage::Format_ARGB32);
    QPainter painter;

    image.fill(Qt::transparent);
    painter.begin(&image);

    int lineWidth = 20;
    int line_padding = 30;
    int line_length = 60;
    int size = 200;
    const int x = 50;
    const int y = 50;
    int rect_size = size;
    int cx = x + rect_size / 2;
    int cy = y + rect_size / 2;

    painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.setPen(QPen(Qt::red, lineWidth, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(cx, cy);
    painter.setPen(QPen(Qt::green, lineWidth, Qt::SolidLine, Qt::RoundCap));

    QRect rectangle(x, y, rect_size, rect_size);
    //painter.drawRect(rectangle);
    painter.drawPoint(x, y);
    painter.drawPoint(x+rect_size, y+rect_size);
    // drawArc, 3 o'clock is 0, +deg is counter-clockwise
    // arcSpan is span of degree, start 30, span 60 means start with
    // 30*16 and go forward CCW 60*16 and stop at 90 deg (12 o'clock)
    painter.setPen(QPen(Qt::darkGray, lineWidth, Qt::SolidLine, Qt::RoundCap));
    painter.drawArc(rectangle, 0, 360*16);
    painter.setPen(QPen(QBrush("#fcc226"), lineWidth, Qt::SolidLine, Qt::FlatCap));
    painter.drawArc(rectangle, arcBegin * 16, arcSpan * 16);


    QJsonArray arr = _jo["junctionElementAngle"].toArray();
    arr.push_back(180);
    arr.push_back(jExitAngle);
    for (int i = 0; i < arr.size(); ++i) {
        int dd = arr[i].toInt();
        int r = size / 2 + (lineWidth >> 1);
        int r1 = rect_size / 2 - (lineWidth >> 1);
        // 3 o'clcok is 0 deg, +deg is clockwise
        int a1 = navi2exit(dd);
        int x1 = 0;
        int y1 = 0;

        int r2 = r1 + line_length;
        int x2 = circle_x(cx, r2, a1);
        int y2 = circle_y(cy, r2, a1);

        Q_UNUSED(line_length);
        Q_UNUSED(line_padding);
        Q_UNUSED(r);
        Q_UNUSED(r1);
        Q_UNUSED(x2);
        Q_UNUSED(y2);

        if (dd == jExitAngle || dd == 180) {
            painter.setPen(QPen(QBrush("#fcc226"), lineWidth, Qt::SolidLine, Qt::FlatCap));
            x1 = circle_x(cx, r1, a1);
            y1 = circle_y(cy, r1, a1);
        } else {
            painter.setPen(QPen(Qt::darkGray, lineWidth, Qt::SolidLine, Qt::FlatCap));
            x1 = circle_x(cx, r, a1);
            y1 = circle_y(cy, r, a1);
        }

        painter.drawLine(x1, y1, x2, y2);

        //painter.drawLine(cx, cy, x1, y1);
    }



    painter.end();
    if (image.save(ofn)) {
        qDebug() << "[INFO] export image:" << ofn;
        return true;
    }

    qDebug() << "[FAIL] failed to export" << ofn;
    return false;
}

