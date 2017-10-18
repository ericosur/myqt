#include "commonutil.h"

bool g_messageVerbose = true;

// using stdc FILE* to write
bool writeStringToFile(const QString& str, const QString& fn)
{
    FILE* fp = fopen(fn.toUtf8().constData(), "w");
    if (fp == NULL) {
        qDebug() << "cannot write file:" << fn;
        return false;
    }
    fprintf(fp, "%s", str.toUtf8().constData());
    fclose(fp);
    //qDebug() << "writeStringToFile(): write to" << fn;
    return true;
}

// using QFile to write
bool writeByteArrayToFile(const QByteArray& arr, const QString& fn)
{
    QFile outFile(fn);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "fail to write file:" << fn;
        return false;
    }
    if ( outFile.write(arr) == -1 ) {
        return false;
    }
    return true;
}

bool readFileToByteArray(QByteArray& arr, const QString& fn)
{
    QFile inFile(fn);
    if (!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "fail to read file:" << fn;
        return false;
    }
    arr = inFile.readAll();
    return true;
}

void use_cout(const QString& msg)
{
    std::cout << msg.toUtf8().data() << std::endl;
}

/**
    \brief myMessageOutput() is customized message handler to redirect qDebug()
**/
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QString txt;
    QString prefix = QString("[%1][%2][%3] ")
                        .arg(QTime::currentTime().toString("HH:mm:ss.zzz"))
                        .arg(qApp->applicationName())
                        .arg(qApp->applicationPid());

    switch (type) {
        case QtDebugMsg:
            txt = prefix + QString("D: %1").arg(msg);
            if (g_messageVerbose)
                use_cout(txt);
            break;
        case QtWarningMsg:
            txt = prefix + QString("W: %1").arg(msg);
            use_cout(txt);
            break;
        case QtCriticalMsg:
            txt = prefix + QString("C: %1").arg(msg);
            use_cout(txt);
            break;
        case QtInfoMsg:
            txt = prefix + QString("I: %1").arg(msg);
            if (g_messageVerbose)
                use_cout(txt);
            break;
        case QtFatalMsg:
            txt = prefix + QString("F: %1").arg(msg);
            use_cout(txt);
            abort();
        default:
            break;
    }
}
