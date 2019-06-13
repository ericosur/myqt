/// \file core.cpp
///

#include "core.h"


#define QSET_INI    "qset.ini"

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core(QObject* parent) : QObject(parent)
{
    init_settings();
    qsrand(qrand());

    connect(this, SIGNAL(quitApp()), qApp, SLOT(quit()));

    foo1 = new ThreadFoo("xray", MyEmptyThread::TH_METHOD1, QString::number(qrand(), 16));
    foo2 = new ThreadFoo("yank", MyEmptyThread::TH_METHOD2, QString::number(qrand(), 16));
    foo3 = new ThreadFoo("zebra", MyEmptyThread::TH_METHOD3, QString::number(qrand(), 16));

    connect(foo1, SIGNAL(started()), this, SLOT(onStarted()));
    connect(foo2, SIGNAL(started()), this, SLOT(onStarted()));
    connect(foo3, SIGNAL(started()), this, SLOT(onStarted()));
    connect(foo1, SIGNAL(threadFinished(const QString&)), this, SLOT(onFinished(const QString&)));
    connect(foo2, SIGNAL(threadFinished(const QString&)), this, SLOT(onFinished(const QString&)));
    connect(foo3, SIGNAL(threadFinished(const QString&)), this, SLOT(onFinished(const QString&)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    m_epoch = new QElapsedTimer;

#ifdef USE_JSONHPP
    std::string appName = qApp->applicationName().toUtf8().data();
    json = { {"app_name", appName} };
#endif
}

Core::~Core()
{
    if (m_timer != nullptr) {
        delete m_timer;
    }
    if (m_setting != nullptr) {
        delete m_setting;
    }
    if (m_epoch != nullptr) {
        delete m_epoch;
    }
    if (foo1 != nullptr) {
        delete foo1;
    }
    if (foo2 != nullptr) {
        delete foo2;
    }
    if (foo3 != nullptr) {
        delete foo3;
    }
}

void Core::init_settings()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    m_setting = new QSettings(QSET_INI, QSettings::IniFormat);
    m_setting->setIniCodec(codec);
    m_setting->clear();

    //m_setting->setValue("editor/wrapMargin", 68);
    //m_setting->setValue("%U4E2D%U6587", "chinese characters");
    //m_setting->setValue("地點/地址", "台北市北投區承德路7段400號");
    qDebug() << "ini path: " << QSET_INI;
}

void Core::start()
{
    m_timer->start(1000);
    m_epoch->start();
    qDebug() << "foo1 start...";
    foo1->start();
    qDebug() << "foo2 start...";
    foo2->start();
    qDebug() << "foo3 start...";
    foo3->start();
}

void Core::onStarted()
{
    m_threadcount ++;
    record_value(QString("start_") + QString::number(m_threadcount),
                 m_epoch->elapsed());

}

#ifdef USE_JSONHPP
void Core::flush_json()
{
    std::ofstream outf(RESULT_JSONFILE);
    outf << json.dump(4);
}
#endif

void Core::checkIfNoThread()
{
    if (m_threadcount <= 0) {
        m_timer->stop();
        m_setting->sync();
#ifdef USE_JSONHPP
        flush_json();
#endif
        emit quitApp();
    }
}

// void Core::sltWaitamoment()
// {

// }

void Core::record_value(const QString& key, quint64 val)
{
    if (m_setting != nullptr) {
        m_setting->setValue(key, val);
    }
#ifdef USE_JSONHPP
    std::string _key = key.toUtf8().data();
    json[_key] = val;
#endif
}

void Core::onFinished(const QString& str)
{
    quint64 e = m_epoch->elapsed();
    qDebug() << Q_FUNC_INFO << str << "@" << e;
    m_threadcount --;
    record_value(str, e);
    checkIfNoThread();
}

void Core::onTimeout()
{
    m_counter ++;
    quint64 e = m_epoch->elapsed();
    m_setting->setValue("last_timeout", m_epoch->elapsed());
#ifdef USE_JSONHPP
    json["last_timeout"] = m_epoch->elapsed();
#endif
    qDebug() << "onTimeout() epoch:" << e << "threads:" << m_threadcount << " timeout:" << m_counter;
}
