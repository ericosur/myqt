/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QMessageBox>
#include <QUuid>

#include "chat.h"
#include "chat_adaptor.h"
#include "chat_interface.h"

#define DBUS_PATH "/qtapp"
#define DBUS_IFACE "com.pega.rasmus"

enum ENUM_BUS {
    USE_SESSION_BUS,
    USE_SYSTEM_BUS
};

ENUM_BUS g_session_bus = USE_SYSTEM_BUS;

QDBusConnection get_bus()
{
    if (g_session_bus == USE_SESSION_BUS) {
        qDebug() << "session bus...";
        return QDBusConnection::sessionBus();
    } else if (g_session_bus == USE_SYSTEM_BUS) {
        qDebug() << "system bus...";
        return QDBusConnection::systemBus();
    } else {
        return QDBusConnection("qtchat");
    }
}

ChatMainWindow::ChatMainWindow()
    : m_nickname(QLatin1String("nickname"))
{
    setupUi(this);
    sendButton->setEnabled(false);

    connect(messageLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(textChangedSlot(QString)));
    connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendClickedSlot()));
    connect(actionChangeNickname, SIGNAL(triggered(bool)), this, SLOT(changeNickname()));
    connect(actionAboutQt, SIGNAL(triggered(bool)), this, SLOT(aboutQt()));
    connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(exiting()));

    // add our D-Bus interface and connect to D-Bus
    new ChatAdaptor(this);
    //QDBusConnection::sessionBus().registerObject(DBUS_PATH, this);
    get_bus().registerObject(DBUS_PATH, this);

    ComPegaRasmusInterface *iface;
    //iface = new ::ComPegaRasmusInterface(QString(), QString(), QDBusConnection::sessionBus(), this);
    iface = new ::ComPegaRasmusInterface(QString(), QString(), get_bus(), this);

    //get_bus().connect(QString(), QString(), DBUS_IFACE, "message", this, SLOT(messageSlot(QString,QString)));
    connect(iface, SIGNAL(message(QString,QString)), this, SLOT(messageSlot(QString,QString)));

    connect(iface, SIGNAL(action(QString,QString)), this, SLOT(actionSlot(QString,QString)));

    //get_bus().connect(QString(), QString(), DBUS_IFACE, "command", this, SLOT(sltCommand(QString)));
    connect(iface, SIGNAL(command(QString)), this, SLOT(sltCommand(QString)));

    m_nickname = QUuid::createUuid().toString();
    emit action(m_nickname, QLatin1String("joins the chat"));
}

ChatMainWindow::~ChatMainWindow()
{
}

void ChatMainWindow::rebuildHistory()
{
    QString history = m_messages.join( QLatin1String("\n" ) );
    chatHistory->setPlainText(history);
}

void ChatMainWindow::messageSlot(const QString &nickname, const QString &text)
{
    qDebug() << Q_FUNC_INFO << nickname << " " << text;
    QString msg( QLatin1String("<%1> %2") );
    msg = msg.arg(nickname, text);
    m_messages.append(msg);

    if (m_messages.count() > 100)
        m_messages.removeFirst();
    rebuildHistory();
}

void ChatMainWindow::actionSlot(const QString &nickname, const QString &text)
{
    qDebug() << Q_FUNC_INFO << nickname << " " << text;
    QString msg( QLatin1String("* %1 %2") );
    msg = msg.arg(nickname, text);
    m_messages.append(msg);

    if (m_messages.count() > 100)
        m_messages.removeFirst();
    rebuildHistory();
}

void ChatMainWindow::sltCommand(const QString &text)
{
    qDebug() << Q_FUNC_INFO << text;
    QString msg( QLatin1String("cmd => %1") );
    msg = msg.arg(text);
    m_messages.append(msg);

    if (m_messages.count() > 100)
        m_messages.removeFirst();
    rebuildHistory();

    if (text == "quit") {
        close();
    }
}

void ChatMainWindow::textChangedSlot(const QString &newText)
{
    sendButton->setEnabled(!newText.isEmpty());
}

void ChatMainWindow::sendClickedSlot()
{
    //emit message(m_nickname, messageLineEdit->text());
    QDBusMessage msg = QDBusMessage::createSignal(DBUS_PATH, DBUS_IFACE, "message");
    msg << m_nickname << messageLineEdit->text();
    get_bus().send(msg);
    messageLineEdit->setText(QString());
}

void ChatMainWindow::changeNickname()
{
    QString old = m_nickname;
    m_nickname = QUuid::createUuid().toString();
    emit action(m_nickname, QLatin1String("joins the chat"));
    emit action(old, QString("is now known as %1").arg(m_nickname));
}

void ChatMainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void ChatMainWindow::exiting()
{
    emit action(m_nickname, QLatin1String("leaves the chat"));
}


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
	bool ret = false;

    g_session_bus = USE_SYSTEM_BUS;
	if (argc > 1 && strcmp(argv[1], "session")==0) {
		g_session_bus = USE_SESSION_BUS;
        ret = QDBusConnection::sessionBus().isConnected();
        qDebug() << "use session bus:" << ret;
	} else {
        ret = QDBusConnection::systemBus().isConnected();
        qDebug() << "use system bus:" << ret;
    }

	if (!ret) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

    ChatMainWindow chat;
    chat.show();
    return app.exec();
}
