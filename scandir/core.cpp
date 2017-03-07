
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
    qDebug() << "read config from:" << config_fn;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings st(fn, QSettings::IniFormat);
    st.setIniCodec(codec);
    //st.setValue("/appname", qApp->applicationName());


    QString _dir = st.value("/startpath", DEFAULT_START_PATH).toString();
    setInputdir(_dir);
    _dir = st.value("/outputpath", DEFAULT_OUTPUT_PATH).toString();
    setOutputdir(_dir);

    int _threadno = st.value("/numberofthread", 1).toInt();
    for (int i=1; i<=_threadno; i++) {
        QString k = QString("/thread%1").arg(i);
        QString _thname = st.value(k, "null").toString();
        k = QString("/filter%1").arg(i);
        QStringList _filter = st.value(k, "").toStringList();
        if (!threadHash.contains(_thname)) {
            qDebug() << "create thread named as:" << _thname;
            TravelThread *tt = new TravelThread(_thname);
            threadHash.insert(_thname, tt);
            tt->setStartPath(input_dir);
            tt->setFilter(_filter);
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

void Core::setOutputdir(const QString& fn)
{
    QDir odir(fn);
    if (odir.exists()) {
        output_dir = fn;
        qDebug() << "will output to:" << output_dir;
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
    // qDebug() << "thread<" << tt->getThreadName() << ">"
    //     << "folder size:" << tt->getFolderhash().size()
    //     << "file size:" << tt->getFilelist().size();

    // dump result into ini
    dumpFolderHash(name, tt->getFolderhash());
    //dumpFilelist(name, tt->getFilelist());

    delete tt;
    if ( threadHash.remove(name) != 1 ) {
        qWarning() << "hash remove error!";
    }
    if ( threadHash.size() <= 0 ) {
        emit sigQuitapp();
    }
}

void Core::dumpFolderHash(const QString& name, const FolderHashList& folderhash)
{
    mutex.lock();
    QString fn = QString("%1/%2_out.ini").arg(output_dir).arg(name);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QSettings st(fn, QSettings::IniFormat);
    st.setIniCodec(codec);

    st.clear();

    // thread name: [video, picture, music]
    st.setValue("/threadname", name);
    // how many folders?
    if (folderhash.contains(input_dir)) {
        // rootdir contains media files
        st.setValue("/size", folderhash.size()-1);
    } else {
        st.setValue("/size", folderhash.size());
    }

    st.setValue("/rootdir", input_dir);

    if (folderhash.size() <= 0) {
        qWarning() << "folder hash list is empty:" << name;
        mutex.unlock();
        return;
    }

    // process rootfolder first
    QString group_name;
    QString folder_name;
    QString key_name;

    int root_size = 0;

    if (folderhash.contains(input_dir)) {
        QStringList *rf = folderhash.value(input_dir);
        st.setValue("/rootdir/fileno", rf->size());
        st.setValue("/rootdir/dirno", folderhash.size()-1);
        root_size = rf->size() + folderhash.size() - 1;
        for (int ii = 0; ii<rf->size(); ii++) {
            st.setValue(QString("/rootdir/f%1").arg(ii), rf->at(ii));
        }
    } else {
        st.setValue("/rootdir/dirno", folderhash.size());
        root_size = folderhash.size();
        qWarning() << "no files at rootdir...";
    }

    st.setValue("/rootdir/totalsize", root_size);


    QStringList folderkeylist = folderhash.keys();
    int dd = 0;
    for (int i = 0; i < folderkeylist.size(); i++) {
        group_name = QString("/folder%1").arg(i);
        folder_name = folderkeylist.at(i);
        key_name = QString("%1/foldername").arg(group_name);
        st.setValue(key_name, folder_name);
        // special for root folder list ---
        if (folder_name != input_dir) {
            st.setValue(QString("/rootdir/folder%1").arg(dd), folder_name);
            dd ++;
            key_name = QString("/folder%1").arg(i);
            st.setValue(key_name, folder_name);
        } else {
            // will skip input_dir as a folder name,
            // it will go to special folder "rootdir"
        }
        // special for root folder list --->
        key_name = QString("%1/size").arg(group_name);
        QStringList* sl = folderhash.value(folder_name);
        st.setValue(key_name, sl->size());

        for (int j = 0; j < sl->size(); j++) {
            key_name = QString("%1/%2").arg(group_name).arg(j);
            st.setValue(key_name, sl->at(j));
        }
    }
    st.sync();
    mutex.unlock();
}
