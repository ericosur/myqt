#include <QtCore>
#include <QDebug>
#include <QHash>
#include <QCryptographicHash>

//#include <QApplication>
#include <iostream>

#define SHOWHEADER()    \
    qDebug() << Q_FUNC_INFO << "===>"

using namespace std;

void test()
{
    QProcess process;
    process.start("du -chs /home/rasmus/gcode/snippet/");
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    qDebug() << "stdout: " << stdout;
    qDebug() << "stderr: " << stderr;
}


QString get_info()
{
    SHOWHEADER();

    QByteArray user = qgetenv("USER");
    QByteArray host = qgetenv("HOSTNAME");
    QString s = QString(user) + "@" + QString(host) + " ";
    QString b = QString(__DATE__) + " " + QString(__TIME__);
    qDebug() << "s: " << s << endl
        << "b: " << b;

    return s;
}

QString getFilenameHash(const QString& fn)
{
    QCryptographicHash hash( QCryptographicHash::Md5 );
    hash.addData(fn.toStdString().c_str(), fn.length());
    QString result = hash.result().toHex().data();
    return result;
}

// ifn: input video filename
QString extractOneFrameFromVideo(const QString& ifn)
{
    SHOWHEADER();

    QString ofn = getFilenameHash(ifn);
    QString cmd = QString("avconv -ss 0:0:10 -i %1 -vsync 1 -t 0.01 %2.png")
                    .arg(ifn).arg(ofn);

    QProcess process;
    process.start(cmd);
    // will it block???
    process.waitForFinished(-1); // will wait forever until finished
    int exitCode = process.exitCode();
    qDebug() << "exit code:" << exitCode;
    // just for debug
    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();
    qDebug() << "stdout: " << stdout;
    qDebug() << "stderr: " << stderr;
    // just for debug

    return ofn;
}

void print_sizeof(const QString& msg, size_t size)
{
    qDebug() << "sizeof" << msg << "is" << size;
}

void print_sz(const std::string msg, size_t size)
{
    std::cout << "[STL] msg: " << msg << ", sizeof: " << size << std::endl;
}

void test_sizeof()
{
    SHOWHEADER();

    using namespace std;

    const char* hello = "hello";
    const char vocano[] = "vocano";
    const string car = "car";
    const QString quickfox = "quickfox";

    print_sizeof(hello, sizeof(hello));
    print_sizeof(vocano, sizeof(vocano));
    print_sz(car, sizeof(car));
    print_sizeof(quickfox, sizeof(quickfox));
}

void test_qhash()
{
    SHOWHEADER();
    QHash<QString, QString> hh = {{"a", "apple"}, {"d", "duck"}, {"m", "monkey"}};

    QHash<QString, QString>::const_iterator it;
    for (it = hh.cbegin(); it != hh.cend(); ++it) {
        qDebug() << *it;
    }
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QString fn = "clip.mp4";
    qDebug() << "md5(fn): " << extractOneFrameFromVideo(fn);

    test_sizeof();

    get_info();

    test_qhash();

    return 0;
}
