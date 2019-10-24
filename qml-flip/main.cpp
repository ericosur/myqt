#include <QGuiApplication>
#include <QQmlContext>
#include <unistd.h>
#include "core.h"

int gHeight = Core::MIN_COREHEIGHT;
int gWidth = Core::MIN_COREWIDTH;

void handleOpt(int argc, char* argv[])
{
    int _h = 0;
    int _w = 0;

    if (argc == 1) {
        return;
    }

    while (true) {
        int c = getopt(argc, argv, "w:h:");
        if (c == -1)
            break;
        switch (c) {
        case 'w':
            _w = QString(optarg).toInt();
            break;
        case 'h':
            _h = QString(optarg).toInt();
            break;
        default:
            break;
        }
    }

    // validate
    if (_w && _w > Core::MIN_COREWIDTH) {
        gWidth = _w;
        qDebug() << "set width to:" << gWidth;
    }
    if (_h && _h > Core::MIN_COREHEIGHT) {
        gHeight = _h;
        qDebug() << "set height to:" << gHeight;
    }
}

int main(int argc, char *argv[])
{
    handleOpt(argc, argv);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine* engine = Core::getInstance()->getEngine();
    Core::getInstance()->hello();
    Core::getInstance()->setCoreWidth(gWidth);
    Core::getInstance()->setCoreHeight(gHeight);

    engine->rootContext()->setContextProperty("core", Core::getInstance());
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
