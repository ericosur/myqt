/// file: nowplaycore.h
#ifndef __CORE_H__
#define __CORE_H__

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QQmlApplicationEngine>
#include <QDebug>

class Core : public QObject
{
    Q_OBJECT

public:
    static Core* getInstance();

    QVariantMap loadJsonToVmap(const QString& fn);

    Q_INVOKABLE void test();

protected:
    static Core* _instance;
    Core();

signals:
    void stateChanged(const QVariantMap& vm);

public slots:

private:

};

#endif  // __CORE_H__
