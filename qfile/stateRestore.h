#ifndef STATERESTORE_H
#define STATERESTORE_H
#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <unistd.h>
#include <QTextCodec>
#include <QUrl>

class stateRestore : public QObject
{
	Q_OBJECT
public:
	stateRestore( QObject* parent = 0 );
	~stateRestore();

	Q_INVOKABLE void clear();
	Q_INVOKABLE void remove( QString key );
	Q_INVOKABLE void saveState( QString key, QVariant value );
	Q_INVOKABLE QVariant readState( QString key, QVariant );
    Q_INVOKABLE void saveSource(QString key,QUrl url);
    Q_INVOKABLE QUrl readSource(QString key,QVariant);
	Q_INVOKABLE void beginGroup( QString group );
	Q_INVOKABLE void endGroup();
	Q_INVOKABLE void forceSync();
    Q_INVOKABLE QUrl getcurrentVideo();
    Q_INVOKABLE void setVideourl(const QString& key ,const QString& url);
private:
	QSettings *q_settings;
};

#endif // STATERESTORE_H
