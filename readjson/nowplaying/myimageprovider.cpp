#include "myimageprovider.h"

#include <QDebug>


MyImageProvider::MyImageProvider(ImageType type, Flags flags) :
    QQuickImageProvider(type,flags)
    , m_value(0)
{
}

MyImageProvider::~MyImageProvider()
{
}


QImage MyImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "requestImage(): id: " << id;
    (void)requestedSize;
    //qDebug() << "reequestedSize: " << requestedSize.width() << " " << requestedSize.height();

    //QImage res = QImage(QString("/home/ericosur/gcode/snippet/qt/qml-flip/prev.jpg"));
    QImage res;
    size->setHeight(500);
    size->setWidth(500);
#if 0
    MyId3Data *id3 = nullptr;
    if ( m_cache.contains(id) ) {
        id3 = m_cache.object(id);
        if (id3 != nullptr) {
            res = id3->get_img();
        } else {
            //qDebug() << "requestImage(): no img";
            res = QImage(); // TODO: use default image
        }
    } else {
        //qDebug() << "requestImage(): img not load...";
        res = QImage(); // TODO: use default image
    }
#endif
    return res;
}
