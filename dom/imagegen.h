#ifndef __UTIL_IMAGE_GENERATOR_H__
#define __UTIL_IMAGE_GENERATOR_H__

#include <QObject>
#include <QString>
#include <QJsonObject>

class ImageGen : public QObject
{
private:

public:
    static ImageGen* getInstance();

    // setter to input parameters
    void setJsonObject(const QJsonObject& jo) {
        _jo = jo;
    }
    bool draw_png(const QString& ofn);

protected:
    static ImageGen* _instance;
    ImageGen();

private:
    QJsonObject _jo;

};

#endif  // __UTIL_IMAGE_GENERATOR_H__
