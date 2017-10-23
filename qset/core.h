/// \file core.h
///

#ifndef __CORE_H__
#define __CORE_H__

#include <QObject>
#include <QCoreApplication>
#include <QTimer>
#include <QSettings>
#include <QElapsedTimer>
#include <QSettings>
#include <QTextCodec>
#include <QDebug>

#ifdef USE_JSONHPP
#include <iostream>
#include <fstream>
#include <json.hpp>
#define RESULT_JSONFILE    "qset_result.json"
#endif

#include "mythreads.h"

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* getInstance();
    ~Core();

    void start();

protected:
    Core(QObject *parent = 0);
    static Core* _instance;

    void init_settings();

signals:
    void quitApp();

public slots:
    void onStarted();
    void onFinished(const QString& str);
    void onTimeout();

private:
    void checkIfNoThread();
    void record_value(const QString& key, quint64 val);

#ifdef USE_JSONHPP
    void flush_json();
#endif

private:
    int m_threadcount = 0;
    int m_counter = 0;
    QTimer *m_timer = NULL;
    QSettings *m_setting = NULL;
    QElapsedTimer *m_epoch = NULL;

    ThreadFoo *foo1 = NULL;
    ThreadFoo *foo2 = NULL;
    ThreadFoo *foo3 = NULL;

#ifdef USE_JSONHPP
    nlohmann::json json;
#endif
};

#endif // __CORE_H__
