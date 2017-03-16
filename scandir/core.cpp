
#include "core.h"

/*
enum MEDIAID {
    BASE_MUSIC_FOLDERID = 0x200000,
    BASE_MUSIC_FILEID = 0x400000,
    BASE_VIDEO_FOLDERID = 0x600000,
    BASE_VIDEO_FILEID = 0x800000,
    BASE_PICTURE_FOLDERID = 0xA00000,
    BASE_PICTURE_FOLDERID = 0xC00000,
    MAX_NUMBER_EACH_ID = 0x1FFFFF
};
*/

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
    connect(this, SIGNAL(sigScanFinish()), this, SLOT(sltScanFinish()));
    connect(this, SIGNAL(sigScanAbort()), this, SLOT(sltScanAbort()));
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
    qDebug() << Q_FUNC_INFO << "scan starts...";
    startThreads();
}

void Core::sltStart()
{
    qDebug() << Q_FUNC_INFO;
}

bool Core::setConfigFilename(const QString& fn)
{
    if ( !isFileExisted(fn) ) {
        qWarning() << "no such file...";
        return false;
    }

    config_fn = fn;
    qDebug() << "read config from:" << config_fn;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings st(fn, QSettings::IniFormat);
    st.setIniCodec(codec);

    QString _dir = st.value("/startpath", DEFAULT_START_PATH).toString();
    if ( !setInputdir(_dir) )
        return false;

    _dir = st.value("/outputpath", DEFAULT_OUTPUT_PATH).toString();
    if ( !setOutputdir(_dir) )
        return false;

    bDebug = st.value("/debug", false).toBool();

    int _threadno = st.value("/numberofthread", 1).toInt();
    for (int i=1; i<=_threadno; i++) {
        QString k = QString("/thread%1").arg(i);
        QString _thname = st.value(k, "null").toString();
        k = QString("/filter%1").arg(i);
        QStringList _filter = st.value(k, "").toStringList();
        basedirid = st.value(QString("basedirid%1").arg(i), 0).toUInt();
        basefileid = st.value(QString("basefileid%1").arg(i), 0).toUInt();

        if (!threadHash.contains(_thname)) {
            qDebug() << "create thread named as:" << _thname;
            TravelThread *tt = new TravelThread(_thname);
            threadHash.insert(_thname, tt);
            tt->setStartPath(input_dir);
            tt->setOutputdir(output_dir);
            tt->setFilter(_filter);
            tt->setBaseDirId(basedirid);
            tt->setBaseFileId(basefileid);
        }
    }
    return true;
}

bool Core::setInputdir(const QString& fn)
{
    QDir idir(fn);

    if (!idir.exists()) {
        qCritical() << "path not found, cannot proceed:" << input_dir;
        emit sigScanAbort();
        return false;
    }

    input_dir = fn;
    qDebug() << "will search:" << input_dir;
    return true;
}

bool Core::setOutputdir(const QString& fn)
{
    QDir odir(fn);
    if (!odir.exists()) {
        qCritical() << "path not found, cannot proceed:" << output_dir;
        emit sigScanAbort();
        return false;
    }

    output_dir = fn;
    qDebug() << "will output to:" << output_dir;
    return true;
}

void Core::sltTravelFinished()
{
    //qDebug() << "thread finished...";
}

void Core::record_md5sum(const QString& name)
{
    QString infn = QString("%1/%2_out.ini").arg(output_dir).arg(name);
    QString cmd = QString("/usr/bin/md5sum %1 > %2.md5").arg(infn).arg(infn);
    if ( system(cmd.toUtf8().data()) == -1 ) {
        qWarning() << "running system() wrong...";
    }
}

void Core::sltThreadNotify(const QString& name)
{
    if (!threadHash.contains(name)) {
        qWarning() << "no such thread name!";
        return ;
    }
    qDebug() << Q_FUNC_INFO << name << "say he has done!";

    //TravelThread* tt = threadHash.value(name);
    // qDebug() << "thread<" << tt->getThreadName() << ">"
    //     << "folder size:" << tt->getFolderhash().size()
    //     << "file size:" << tt->getFilelist().size();
    // dump result into ini
    //dumpFolderHash(name, tt->getFolderhash());
    //dumpFilelist(name, tt->getFilelist());
    //delete tt;

    record_md5sum(name);

    if ( threadHash.remove(name) != 1 ) {
        qWarning() << "hash remove error!";
    }
    if ( threadHash.size() <= 0 ) {
        emit sigScanFinish();
    }
}

void Core::sltScanFinish()
{
    // notify app to quit
    emit sigQuitapp();
}

void Core::sltScanAbort()
{
    emit sigQuitapp();
}
