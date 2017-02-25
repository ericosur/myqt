
#include "core.h"

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
    connect(this, SIGNAL(sigStart()), this, SLOT(sltStart()));
}

void Core::startThreads()
{
    foreach (QString threadname, threadHash.keys()) {
        TravelThread *tt = threadHash.value(threadname);
        connect(tt, SIGNAL(finished()), this, SLOT(sltTravelFinished()));
        connect(tt, SIGNAL(sigThreadNotify(const QString&)),
                this, SLOT(sltThreadNotify(const QString&)));
        qDebug() << "thread:" << threadname
            << "launched...";
        tt->start();
    }
}

void Core::start()
{
    qDebug() << Q_FUNC_INFO;

    startThreads();
}

void Core::sltStart()
{
    qDebug() << Q_FUNC_INFO;
}



void Core::setConfigFilename(const QString& fn)
{
    if ( !isFileExisted(fn) ) {
        qWarning() << "no such file...";
        return;
    }

    config_fn = fn;
    qDebug() << "will read:" << config_fn;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings st(fn, QSettings::IniFormat);
    st.setIniCodec(codec);
    st.setValue("/appname", qApp->applicationName());
    //
    QString _dir = st.value("/startpath", "/home/ericosur/Dropbox").toString();
    setInputdir(_dir);

    int _threadno = st.value("/numberofthread", 1).toInt();
    for (int i=1; i<=_threadno; i++) {
        QString k = QString("/thread%1").arg(i);
        QString _thname = st.value(k, "null").toString();
        if (!threadHash.contains(_thname)) {
            qDebug() << "create thread named as:" << _thname;
            TravelThread *tt = new TravelThread(_thname);
            threadHash.insert(_thname, tt);
            tt->setStartPath(input_dir);
        }
    }
}

void Core::setInputdir(const QString& fn)
{
    QDir idir(fn);
    if (idir.exists()) {
        input_dir = fn;
        qDebug() << "will search:" << input_dir;
    }
}

void Core::sltTravelFinished()
{
    //qDebug() << "thread finished...";
}

void Core::sltThreadNotify(const QString& name)
{
    qDebug() << Q_FUNC_INFO << name;
    if (!threadHash.contains(name)) {
        qWarning() << "no such thread name!";
        return ;
    }

    TravelThread* tt = threadHash.value(name);
    qDebug() << "thread<" << tt->getThreadName() << ">"
        << "folder size:" << tt->getFolderhash().size()
        << "file size:" << tt->getFilelist().size();
    delete tt;
    if ( threadHash.remove(name) != 1 ) {
        qWarning() << "hash remove error!";
    }
    if ( threadHash.size() <= 0 ) {
        emit sigQuitapp();
    }
}
