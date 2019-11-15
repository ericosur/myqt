#include "loadtext.h"

#include <QFile>
#include <QDebug>

LoadText::LoadText(QObject* parent) :
    QObject(parent)
{
}

QString LoadText::message()
{
    return m_text;
}

void LoadText::setMessage(const QString& str)
{
    if (str == m_text) {
        // do nothing
        qWarning() << "do nothing...";
        return;
    }
    m_text = str;
    emit messageChanged();
}

QString LoadText::getTextWithId(LangType id)
{
    QString fn;
    QString content;
    qDebug() << Q_FUNC_INFO << "id:" << id;
    if (m_map.contains(id)) {
        fn = QString(":/txt/%1.txt").arg(m_map.value(id));
        content = readTextfile(fn);
#ifdef Q_WS_WIN
        //content = content.toLocal8Bit();
#endif
    }
    QString str = QString("get with id: %1\n%2").arg(fn)
            .arg(content);
    setMessage(str);
    //qDebug() << "str:" << str;

    return str;
}

QString LoadText::readTextfile(const QString& fn)
{
    qDebug() << "fn:" << fn;
    QFile data(fn);
    QString str;
    if (data.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream textStream(&data);
        while (true) {
            QString line = textStream.readLine();
            // will skip null line
            if (line.isNull()) {
                break;
            }
            str = str + line;
        }
    }
    return str;
}
