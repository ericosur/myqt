#ifndef __UTIL_EMOJICORE_H__
#define __UTIL_EMOJICORE_H__

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>

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
        emit sequenceChanged();
    }

    void load_tests();

signals:
    void sequenceChanged();

public slots:
    void sltTimeout();

protected:
    static EmojiCore* _instance;
    EmojiCore(QObject *_parent=NULL);

    void test0();
    void test1();

    QStringList string_to_codepoint_list(const QString& s);
    QString parse_codepoint_list(const QStringList& sl);

private:
    QTimer* test_timer = NULL;
    QStringList test_list;
    QString mSeq = "";
    QStringList emojiList = {
#include "emoji-list.inc"
    };
};


#endif  // __UTIL_EMOJICORE_H__
