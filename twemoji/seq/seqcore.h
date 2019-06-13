#ifndef __UTIL_SEQCORE_H__
#define __UTIL_SEQCORE_H__

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

class SeqCore : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)


public:
    static SeqCore* getInstance();

    void setCodepointSequence(const QStringList& tl);
    QString getEmojiSequence() const {
        return emoji_ans;
    }

    void test();

signals:

public slots:

protected:
    static SeqCore* _instance;
    SeqCore(QObject *_parent=nullptr);

    void load_from_res();
    void load_seq();
    bool lookup_list(const QStringList& t);
    bool get_possible_len(const QStringList& t, QList<int>& pls);
    bool get_possible_len(const QString& k, QList<int>& pls);
    QStringList get_trylist(const QStringList& t, int try_len);

    bool match(const QStringList& tl);

    void add_to_answer(const QStringList& sl);
    void pop_to_answer(const QString& s);

private:
    QMap<QString, QList<QStringList>> qq;
    int key_count = 0;
    QByteArray ba_buffer;
    QString emoji_ans;

    bool isDebug = false;
};


#endif  // __UTIL_SEQCORE_H__
