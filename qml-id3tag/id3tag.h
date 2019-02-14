#ifndef __ID3TAG_H__
#define __ID3TAG_H__

#include <QObject>

QT_BEGIN_NAMESPACE
#include <QImage>
#include <QCache>
QT_END_NAMESPACE

#include "myid3data.h"

class ID3TAG : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString filename READ getFilename WRITE setFilename)
    Q_PROPERTY(QString title READ getTitle)
    Q_PROPERTY(QString artist READ getArtist)
    Q_PROPERTY(QString album READ getAlbum)
    Q_PROPERTY(QImage cover READ getCover)
    Q_PROPERTY(QString fn1 READ fn1 WRITE setFn1 NOTIFY fn1Changed)
    Q_PROPERTY(QString fn2 READ fn2 WRITE setFn2 NOTIFY fn2Changed)

public:
    ID3TAG(QObject *parent = 0);
    ~ID3TAG();

    QString getFilename() const;
    void setFilename(const QString& s); // will invoke getMetaData()
    QString getTitle() const;
    QString getArtist() const;
    QString getAlbum() const;
    QImage getCover() const;
    QString getCoverPath() const;

    QString fn1() const {
        return m_fn1;
    }
    void setFn1(const QString& f) {
        if (m_fn1 != f) {
            m_fn1 = f;
            emit fn1Changed();
        }
    }
    QString fn2() const {
        return m_fn2;
    }
    void setFn2(const QString& f) {
        if (m_fn2 != f) {
            m_fn2 = f;
            emit fn2Changed();
        }
    }

public:
    Q_INVOKABLE void init();
    // invoke this function to load/store id3 tags
    Q_INVOKABLE bool getMetaData(const QString& fn);

signals:
    void fn1Changed();
    void fn2Changed();

protected:
    QString getHashFilename(const QString& fn);
    bool getdata(MyId3Data* id3);

private:
    QString m_filename;
    QString m_title;
    QString m_artist;
    QString m_album;
    QImage  m_cover;

    QString m_fn1;
    QString m_fn2;
};

// key: fn, value: myid3data
extern QCache<QString, MyId3Data> m_cache;

#endif // __ID3TAG_H__
