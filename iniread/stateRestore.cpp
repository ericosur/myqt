#include "stateRestore.h"
#include <QFile>
#include <QDir>


#ifdef USE_YOSETARGET
#define DEFAULT_INI_PATH    "/data/apps/mediaui.ini"
#else
#define DEFAULT_INI_PATH    "/tmp/mediaui.ini"
#endif

stateRestore::stateRestore( QObject* parent ) :
	QObject( parent ),
	q_settings(nullptr)
{
	QString ini_path = DEFAULT_INI_PATH;
	QFile file(DEFAULT_INI_PATH);
	if(!file.open(QIODevice::ReadOnly)) {
		int index = ini_path.lastIndexOf("/");
		QString path = ini_path.left(index);
		QDir fir  = QDir::root();
		fir.mkdir(path);
	}
	q_settings = new QSettings(DEFAULT_INI_PATH, QSettings::NativeFormat);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	q_settings->setIniCodec(codec);
}

stateRestore::~stateRestore()
{

}

void stateRestore::remove(QString key)
{
	q_settings->remove( key );
}

void stateRestore::clear()
{
	q_settings->clear();
}

void stateRestore::saveState(QString key, QVariant value)
{
	q_settings->setValue( key, value );
}

void stateRestore::saveSource(QString key, QUrl url)
{
    QString str_source = url.toLocalFile();
    qDebug()<<"str_source::"<<str_source;
    q_settings->setValue(key,str_source);
}

void stateRestore::saveString(const )

QUrl stateRestore::readSource(QString key, QVariant defaultVal )
{
    QUrl url;
    QString file  = q_settings->value( key, defaultVal ).toString();
    url = QUrl::fromLocalFile(file);
    qDebug()<<Q_FUNC_INFO<<" "<<url;
    return url;
}

QVariant stateRestore::readState(QString key, QVariant defaultVal )
{
	return q_settings->value( key, defaultVal );
}

void stateRestore::beginGroup(QString group)
{
	q_settings->beginGroup( group );
}

void stateRestore::endGroup()
{
	q_settings->endGroup();
	q_settings->sync();
}

// Note!! This is a temporary solution and should be modified in the future.
void stateRestore::forceSync()
{
	sync();
}

QUrl stateRestore::getcurrentVideo()
{
    QSettings m_setting("/data/apps/videorestore.ini",QSettings::IniFormat);
    QString videopath;
    videopath = m_setting.value("videoRestoreURL","").toString();
    QUrl url_video = QUrl::fromLocalFile(videopath);
    return url_video;
}

void stateRestore::setVideourl(const QString& key, const QString& url){
    QSettings m_setting("/data/apps/videorestore.ini",QSettings::IniFormat);
    m_setting.setValue(key,url);
}
