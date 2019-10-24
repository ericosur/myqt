#ifndef __CFGJSON_TEST_H__
#define __CFGJSON_TEST_H__

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonArray>

#ifdef USE_YOSETARGET
const QString DEFAULT_CONFIG_DIR = "/media/usb/storage";
static const QString DEFAULT_CONFIG_FILE = "/media/usb/storage/radiocfg.json";
#else
const QString DEFAULT_CONFIG_DIR = "/tmp";
static const QString DEFAULT_CONFIG_FILE = "../radiocfg.json";
#endif


class GetRadioConfig : public QObject
{
    Q_OBJECT

private:
    const QString JSONFILE = "../radiocfg.json";
    const QString PREFIX = "Radio_register";

    const int TEST_REPEAT = 5;
    const int MAX_KNOWN_CFG_INDEX = 27;
    const QString DEFAULT_INVALID_VALUE = "FF";

public:
    //Q_PROPERTY(QStringList categorylist READ categorylist WRITE setCategorylist NOTIFY categorylistChanged)

    Q_INVOKABLE QString get_cfg_name(int index);
    Q_INVOKABLE QString get_cfg_id(int index);
    Q_INVOKABLE QString get_cfg_value(int index);
    Q_INVOKABLE void set_cfg_value(int index, const QString& value);
    Q_INVOKABLE bool set_cfg_elem(int index, const QString& name, const QString& id,
                                  const QString& value);

    Q_INVOKABLE void browse_dir();
    Q_INVOKABLE void read_all();
    Q_INVOKABLE void write_all();

public:
    static GetRadioConfig* getInstance();

    bool get_cfg_elem(int index, QString& name, QString& id, QString& value);
    bool load_file(const QString& fn);

    void test();
    void test_dir();
    void test_from_scratch();

protected:
    GetRadioConfig();
    static GetRadioConfig* _instance;

private:
    QString get_rand_number();
    void init();
    void init_new_arr();
    void write_header();
    int get_read_count() const {
        return read_arr.count();
    }
    int get_out_count() const {
        return new_arr.count();
    }
    QString get_out_json_filename();
    bool writeByteArrayToFile(const QByteArray& arr, const QString& fn);
    QStringList travel_dir(const QString& path);
    bool check_value(const QString& value);

private:
    QJsonArray read_arr;
    QJsonArray new_arr;
    QStringList file_list;
};


#endif
