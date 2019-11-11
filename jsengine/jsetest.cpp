#include "jsetest.h"

#include <QCoreApplication>
#include <QFile>
#include <QJSValue>
#include <QJSValueList>
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QDebug>

const QString DEAFULT_JS = QString("../test.js");
const int ARRAY_SIZE = 10;

JSETest* JSETest::_instance = nullptr;
JSETest* JSETest::getInstance()
{
    if (_instance == nullptr) {
        _instance = new JSETest();
    }
    return _instance;
}

JSETest::JSETest(QObject* parent) :
    QObject(parent)
{
    engine.installExtensions(QJSEngine::ConsoleExtension);
    connect(this, SIGNAL(sigFinished()), qApp, SLOT(quit()), Qt::QueuedConnection);
}

void JSETest::load(const QString& fn)
{
    qDebug() << Q_FUNC_INFO << "load js from:" << fn;
    QFile scriptFile(fn);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        qDebug() << "SCRIPT file not loaded!";
        emit sigFinished();
        return;
    }
    isLoaded = true;
    QTextStream stream(&scriptFile);
    contents = stream.readAll();
    scriptFile.close();
}

void JSETest::set_property()
{
    qDebug() << Q_FUNC_INFO;
    QJSValue v = "hello world";

    engine.globalObject().setProperty("myNumber", 123);
    QJSValue myNumberPlusOne = engine.evaluate("myNumber + 1");
}

void JSETest::exec()
{
    QJSValue ret = engine.evaluate(contents);
    qDebug() << ret.toString();
    emit sigFinished();
}

void JSETest::test()
{
#if 0
    load(DEAFULT_JS);
    set_property();

    qDebug() << "call exec()";
    exec();
#endif

    QJSValueList args;
    QJSValue func;
    QJSValue result;
    QJSValue module = engine.importModule("math.js");
#if 0
    // 1
    qDebug() << "call sum...";
    args << 79 << 11;

    func = module.property("sum");
    result = func.call(args);
    qDebug() << "result:" << result.toString();
#endif
#if 0
    // 2
    qDebug() << "call randint...";
    args.clear();
    args << 100;
    func = module.property("randint");
    for (int i = 0; i < ARRAY_SIZE; i ++) {
        result = func.call(args);
        qDebug() << "result:" << result.toString();
    }
#endif
#if 0
    // 3
    qDebug() << "call pick_one...";
    func = module.property("pick_one");

    QJSValue jsArray = engine.newArray(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE * 4; ++i) {
        //jsArray.setProperty(i, QRandomGenerator::global()->generate());
        jsArray.setProperty(i, i);
    }
    args.clear();
    args << jsArray;

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        result = func.call(args);
        qDebug() << "result:" << result.toString();
    }
#endif
    // 4
    args.clear();
    args << R"(
    {
        "value": "hello world",
        "Image": {
            "Width":  800,
            "Height": 600,
            "Title":  "View from 15th Floor",
            "Thumbnail": {
                "Url":    "http://www.example.com/image/481989943",
                "Height": 125,
                "Width":  100
            },
            "Animated" : false,
            "IDs": [
                "apple",
                "ball",
                "cat"
            ]
        }
    }
    )";
    func = module.property("get_value");
    result = func.call(args);
    qDebug() << "result:" << result.toString();

    // 5: how to expose C++ class JSETest to javascript
    QJSValue myTestClassObject = engine.newQObject(this);
    engine.globalObject().setProperty("JSETest", myTestClassObject);

    func = module.property("hello_world");
    result = func.call(args);
    qDebug() << "result:" << result.toString();

    emit sigFinished();
}

QString JSETest::md5sum(const char* buffer, int size)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(buffer, size);
    QString str_hash = hash.result().toHex().data();
    return str_hash;
}

QString JSETest::getMd5sum(const QString& s)
{
    return JSETest::md5sum(s.toUtf8(), s.size());
}
