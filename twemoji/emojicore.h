#ifndef __UTIL_EMOJICORE_H__
#define __UTIL_EMOJICORE_H__

#include <QObject>
#include <QString>
#include <QStringList>

class EmojiCore : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)

public:
    static EmojiCore* getInstance();

    QString sequence() const {
        return mSeq;
    }
    void setSequence(const QString& s) {
        mSeq = s;
    }

    void test();
    void test1();

    void parse(const QStringList& sl);

signals:
    void sequenceChanged();

protected:
    static EmojiCore* _instance;
    EmojiCore(QObject *_parent=NULL);

private:
    QString mSeq = "hello world";
    QStringList emojiList = {
#include "emoji-list.inc"
    };
};


#endif  // __UTIL_EMOJICORE_H__
