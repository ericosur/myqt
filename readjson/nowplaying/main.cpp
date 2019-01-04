#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "npcore.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // register my own image provider
    // MyImageProvider *imageProvider = new MyImageProvider(QQmlImageProviderBase::Image);
    // QObject::connect(imageProvider, SIGNAL(valueChanged(int)), imageProvider, SLOT(setValue(int)));

    QQmlApplicationEngine engine;
    //engine.addImageProvider("myprovider", imageProvider);
    engine.rootContext()->setContextProperty("core", NowPlayingCore::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
