#ifndef __UTIL_SEQCORE_H__
#define __UTIL_SEQCORE_H__

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QMap>

class SeqCore : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)


public:
    static SeqCore* getInstance();

    void test();

signals:

public slots:

protected:
    static SeqCore* _instance;
    SeqCore(QObject *_parent=NULL);

    void load_seq();
    bool lookup_list(const QStringList& t, QString& ans);
    bool get_possible_len(const QStringList& t, QList<int>& pls);
    bool get_possible_len(const QString& k, QList<int>& pls);
    QStringList get_trylist(const QStringList& t, int try_len);

    void travel_sequence(const QStringList& tl);
    bool match(const QStringList& tl);

    void pop(const QString& s);

private:
    QMap<QString, QList<QStringList>> qq;
};


#endif  // __UTIL_SEQCORE_H__
