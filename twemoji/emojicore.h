#ifndef __UTIL_EMOJICORE_H__
#define __UTIL_EMOJICORE_H__

#include <QObject>
#include <QString>
#include <QStringList>


class EmojiCore : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)
    Q_PROPERTY(QString instr READ instr WRITE setInstr NOTIFY instrChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    static EmojiCore* getInstance();
    void runTest(const QStringList& sl);

public:
    QString sequence() const {
        return mSeq;
    }
    void setSequence(const QString& s) {
        mSeq = s;
        emit sequenceChanged();
    }
    QString instr() const {
        return mInstr;
    }
    void setInstr(const QString& s) {
        mInstr = s;
        emit instrChanged();
    }
    int count() const {
        return mCount;
    }
    void setCount(int v) {
        mCount = v;
        emit countChanged();
    }

signals:
    void sigQuit();
    void sequenceChanged();
    void instrChanged();
    void countChanged();

public slots:
    void sltCountChanged();

protected:
    static EmojiCore* _instance;
    EmojiCore(QObject *_parent=NULL);

    void test0();
    void test1();

    void load_tests();
    QStringList string_to_codepoint_list(const QString& s);

private:
    int list_idx = 0;

    QStringList test_list;
    QString mSeq;
    QString mInstr;

    int repeat_count = 0;
    int mCount = 0;
};


#endif  // __UTIL_EMOJICORE_H__
