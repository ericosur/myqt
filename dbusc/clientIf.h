/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -v -c clientIf -p clientIf.h:clientIf.cpp hu.MainUi.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef CLIENTIF_H
#define CLIENTIF_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface local.interfacedescription
 */
class clientIf: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "local.interfacedescription"; }

public:
    clientIf(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~clientIf();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QString> SendMessage(const QString &cmd)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(cmd);
        return asyncCallWithArgumentList(QStringLiteral("SendMessage"), argumentList);
    }

    inline QDBusPendingReply<QString> read()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("read"), argumentList);
    }

    inline QDBusPendingReply<QString> write()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("write"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void somethingHappened(const QString &signalMessage);
};

namespace local {
  typedef ::clientIf interfacedescription;
}
#endif
