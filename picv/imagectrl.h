/**
 * \file imagectrl.h
 */

#ifndef __IMAGE_CTRL_H__
#define __IMAGE_CTRL_H__

#include <QObject>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QTimer>
#include <QUrl>
#include <QDebug>

#include "inireader.h"

class ImageCtrl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QUrl imageUrl READ imageUrl WRITE setImgurl NOTIFY imgurlChanged)


public:
    static ImageCtrl* getInstance();

    Q_INVOKABLE void goPrev();
    Q_INVOKABLE void togglePlay();
    Q_INVOKABLE void goNext();

public:
    int currentIndex() {
        return m_curridx;
    }
    void setCurrentIndex(int i);
    QUrl imageUrl();
    void setImgurl(const QUrl& fn);

signals:
    void currentIndexChanged();
    void imgurlChanged();

public slots:
    void sltTimeout();
    void sltUpdate();

protected:
    static ImageCtrl* _instance;
    ImageCtrl();

    void requestNext();
    void requestPrev();

private:
    QTimer* auto_timer = NULL;
    int m_curridx = -1;
    int m_maxidx = 10;
    QUrl imgUrl;

};


#endif // __IMAGE_CTRL_H__
