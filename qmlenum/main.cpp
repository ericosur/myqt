#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>

//#include "commonutil.h"
#include "rcommon.h"

EnumCommonDefineType test_typedef()
{
    return RCommon::CD_START;
}

int main(int argc, char* argv[])
{
    //qInstallMessageHandler(myMessageOutput);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<RCommon>("com.rasmus", 2, 0, "NoshDefine");

    RCommon rcommon;
    engine.rootContext()->setContextProperty("rcommon", &rcommon);

    qDebug() << "test_typedef:" << test_typedef();
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
