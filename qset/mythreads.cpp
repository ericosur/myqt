#include "mythreads.h"


MyEmptyThread::MyEmptyThread()
{
}

QByteArray MyEmptyThread::doHash(int repeat_times, QCryptographicHash::Algorithm algo)
{
    QByteArray data;

    for (int i=0; i<repeat_times; ++i) {
        data.append(qrand());
        for (int j=0; j<repeat_times; ++j) {
            data.append(qrand());
            data = QCryptographicHash::hash(data, algo);
            for (int k=0; k<repeat_times; ++k) {
                data = QCryptographicHash::hash(data, algo);
                data.append( QCryptographicHash::hash(QByteArray(QString::number(qrand(),16).toUtf8()),
                                                      algo) );
                data.append(qrand());
            }
        }
        data = QCryptographicHash::hash(data, algo);
    }
    return data;
}

QString MyEmptyThread::doHardWork(const QString& s, THREAD_METHOD method)
{
    QByteArray data;

    //qDebug() << "doHardWork()" << s << "," << method;
    data.append(s);
    switch (method) {
    case TH_METHOD1:
        data = doHash(MAX_HASH_REPEAT_METHOD_1, QCryptographicHash::Sha3_256);
        break;
    case TH_METHOD2:
        data = doHash(MAX_HASH_REPEAT_METHOD_2, QCryptographicHash::Sha512);
        break;
    case TH_METHOD3:
        data = doHash(MAX_HASH_REPEAT_METHOD_3, QCryptographicHash::Sha3_512);
        break;
    case TH_NULL:
    default:
        qDebug() << "no such method...";
        break;
    }

    return data.toHex().data();
}

/////////////////////////////////////////////////////////////////////
///
///
/// \brief ThreadFoo::ThreadFoo
///
///
/////////////////////////////////////////////////////////////////////
ThreadFoo::ThreadFoo(const QString& name, THREAD_METHOD method, const QString& str) :
    MyEmptyThread(),
    mMethod(method),
    mStr(str),
    mName(name)
{
    connect(this, SIGNAL(finished()), this, SLOT(onFinished()));
}

void ThreadFoo::run()
{
    for (int i = 0; i < MAX_TEST_REPEAT; ++i) {
        ThreadFoo::doHardWork(mStr, mMethod);
    }
}

void ThreadFoo::onFinished()
{
    emit threadFinished(this->getName());
}
