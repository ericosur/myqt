#ifndef __CORE__H__
#define __CORE__H__

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QDebug>

#define MIN_COREWIDTH       500
#define MIN_COREHEIGHT      600

class Core: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int coreWidth READ coreWidth WRITE setCoreWidth NOTIFY coreWidthChanged)
    Q_PROPERTY(int coreHeight READ coreHeight WRITE setCoreHeight NOTIFY coreHeightChanged)

public:
    int coreWidth() const {
        return mCoreWidth;
    }
    void setCoreWidth(int w) {
        mCoreWidth = w;
        emit coreWidthChanged();
    }
    int coreHeight() const {
        return mCoreHeight;
    }
    void setCoreHeight(int h) {
        mCoreHeight = h;
        emit coreHeightChanged();
    }

signals:
    void coreWidthChanged();
    void coreHeightChanged();

public:
    static Core* getInstance();
    void hello();
    QQmlApplicationEngine* getEngine();

protected:
    Core();
    static Core* _instance;

private:
    QQmlApplicationEngine* mEngine = nullptr;
    int mCoreWidth = MIN_COREWIDTH;
    int mCoreHeight = MIN_COREHEIGHT;
};

#endif  // __CORE__H__
