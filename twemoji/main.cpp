#include "emojicore.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>
#include <QDebug>


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QGuiApplication app(argc, argv);

    EmojiCore* emojicore = EmojiCore::getInstance();
    QObject::connect(emojicore, SIGNAL(sigQuit()), &app, SLOT(quit()));

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("emoji", emojicore);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
