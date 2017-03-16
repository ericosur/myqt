/**
 * \file imagectrl.cpp
 */

#include "imagectrl.h"

ImageCtrl* ImageCtrl::_instance = NULL;
ImageCtrl* ImageCtrl::getInstance()
{
    if (_instance == NULL) {
        _instance = new ImageCtrl();
    }

    return _instance;
}

ImageCtrl::ImageCtrl()
{
    if (auto_timer == NULL) {
        auto_timer = new QTimer(this);
        connect(auto_timer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
    }

    connect(this, SIGNAL(currentIndexChanged()), this, SLOT(sltUpdate()));

    IniReader::getInstance()->startRead();

    qDebug() << Q_FUNC_INFO << "created";
}

void ImageCtrl::setCurrentIndex(int i)
{
    if (i < 0) {
        return;
    }

    if (i >= 0 && i < m_maxidx) {
        m_curridx = i;
        emit currentIndexChanged();
        return;
    }

    if (i >= m_maxidx) {
        if (auto_timer->isActive())  {
            auto_timer->stop();
        }
    }
}

QUrl ImageCtrl::imageUrl()
{
    if (imgUrl.isValid()) {
        return imgUrl;
    }
    return QUrl();
}

void ImageCtrl::setImgurl(const QUrl& _url)
{
    imgUrl = _url;
    emit imgurlChanged();
}

void ImageCtrl::goPrev()
{
    //qDebug() << Q_FUNC_INFO;
    requestPrev();
}

void ImageCtrl::togglePlay()
{
    qDebug() << Q_FUNC_INFO;
    if (auto_timer->isActive()) {
        auto_timer->stop();
    } else {
        auto_timer->start(1000);
    }
}

void ImageCtrl::goNext()
{
    //qDebug() << Q_FUNC_INFO;
    requestNext();
}

void ImageCtrl::requestNext()
{
    //qDebug() << Q_FUNC_INFO;
    setCurrentIndex(m_curridx + 1);
}

void ImageCtrl::requestPrev()
{
    //qDebug() << Q_FUNC_INFO;
    setCurrentIndex(m_curridx - 1);
}

void ImageCtrl::sltTimeout()
{
    qDebug() << Q_FUNC_INFO;
    requestNext();
}

void ImageCtrl::sltUpdate()
{
    QString fn = IniReader::getInstance()->requestBySmallId(m_curridx);
    setImgurl(QUrl::fromLocalFile(fn));
}
