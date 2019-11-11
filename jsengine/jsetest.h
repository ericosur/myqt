/**
 * \file jsetest.h
 * \brief class JSETest here
 */
#ifndef __TEST_JSE_TEST_H__
#define __TEST_JSE_TEST_H__

#include <QObject>
#include <QString>
#include <QJSEngine>


/**
 * \class ImgTest
 * \brief singleton class for testing QImage manipulation functions
 */
class JSETest : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString getName() {
        return "My name is JSETest";
    }

    Q_INVOKABLE QString getMd5sum(const QString& s);

public:
    static JSETest* getInstance();

    /**
     * @param fn [in] load specified file
     */
    void load(const QString& fn);

    void set_property();

    /**
     * @brief execute loaded content
     */
    void exec();

    void test();

    /**
     * @brief JSETest::md5sum take md5sum from a buffer with size
     * @param buffer [in] input buffer
     * @param size [in] buffer size
     * @return md5 hash value as string
     */
    static QString md5sum(const char* buffer, int size);

signals:
    void sigFinished();

protected:
    static JSETest* _instance;
    explicit JSETest(QObject* parent=nullptr);

private:
    bool isLoaded = false;
    QJSEngine engine;
    QString contents;
};

#endif	// __TEST_JSE_TEST_H__
