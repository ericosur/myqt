#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>

#include "core.h"
#include "commonutil.h"
#include "rcommon.h"

EnumCommonDefineType test_typedef()
{
    return RCommon::CD_START;
}

void test_play()
{
    Core::getInstance()->playFile("hello.mp3");
    Core::getInstance()->pause();
    Core::getInstance()->playFile("unknown.abc");
    Core::getInstance()->pause();
    Core::getInstance()->playFile("party.mp4");
    Core::getInstance()->pause();
}

int main(int argc, char* argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    // name #3
    qmlRegisterType<RCommon>("com.rasmus", 2, 0, "NoshDefine");

    qDebug() << "test_typedef:" << test_typedef();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    test_play();

    return app.exec();
}
