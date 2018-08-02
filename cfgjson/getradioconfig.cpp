#include "getradioconfig.h"
#include "readjson.h"

#include <QByteArray>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>
#include <QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
#include <QRandomGenerator>
#else
#error Qt is too old to build
#endif

#define JSONFILE    "../radiocfg.json"
//#define OUT_JSON    "/tmp/o.json"
//#define REPEAT      4
#define PREFIX      "Radio_register"

#ifndef USE_YOSETARGET
#define DEFAULT_CONFIG_DIR     "/tmp"
#define DEFAULT_CONFIG_FILE    "../radiocfg.json"
#else
#define DEFAULT_CONFIG_DIR     "/media/usb/storage"
#define DEFAULT_CONFIG_FILE    "/media/usb/storage/radiocfg.json"
#endif


GetRadioConfig* GetRadioConfig::_instance = NULL;
GetRadioConfig* GetRadioConfig::getInstance()
{
    if (_instance == NULL) {
        _instance = new GetRadioConfig();
    }
    return _instance;
}

GetRadioConfig::GetRadioConfig()
{
    init();
}

void GetRadioConfig::init()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
    (void)0;
#else
    qsrand((quint32)QDateTime::currentMSecsSinceEpoch());
#endif

    init_new_arr();
}

void GetRadioConfig::init_new_arr()
{
    while (!new_arr.isEmpty()) {
        new_arr.removeFirst();
    }

    write_header();
}

bool GetRadioConfig::load_file(const QString& fn = DEFAULT_CONFIG_FILE)
{
    ReadJson rj;

    if (!rj.loadFile(fn)) {
        qWarning() << "failed to load";
        return false;
    }

    read_arr = rj.getLeafArray("config");
    qDebug() << "loaded array count:" << get_read_count();

    return true;
}

void GetRadioConfig::write_header()
{
    QDateTime _now = QDateTime::currentDateTime();

    QJsonObject _obj;
    _obj.insert("name", "start");
    _obj.insert("id", "null");
    _obj.insert("value", "FF");
    _obj.insert("created_date", _now.toString("yyyy/MM/dd hh:mm:ss"));
    new_arr.push_back(QJsonValue(_obj));
}

QString GetRadioConfig::get_out_json_filename()
{
    QString opath = "/tmp";
    QString now_str = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString fn = QString("%1/%2_%3%4").arg(opath)
                                      .arg(PREFIX)
                                      .arg(now_str)
                                      .arg(".cfg");
    return fn;
}

QString GetRadioConfig::get_rand_number()
{
    quint32 _tmp = 0xFF;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
    //qDebug() << "using QRandomGenerator...";
    _tmp = QRandomGenerator::global()->generate();
#else
    _tmp = qrand();
#endif

    quint8 value = _tmp % 255 + 1;
    QString result;
    QString tmp = QString::number(value, 16).toUpper();
    if (value < 0x10) {
        result = QString("0%1").arg(tmp);
    } else {
        result = tmp;
    }
    return result;
}

bool GetRadioConfig::get_cfg_elem(int index, QString& name, QString& id, QString& value)
{
    name = "no-name";
    id = "no-id";
    value = "FF";
    if (index <= 0 || index >= read_arr.count()) {
        qWarning() << "ERROR: request out-of-range";
        return false;
    }
    QJsonObject _obj = read_arr.at(index).toObject();
    name = _obj["name"].toString();
    id = _obj["id"].toString();
    QString _val = _obj["value"].toString();
    if (!check_value(_val)) {
        qWarning() << "WARNING: get_cfg_elem:"
            << "from index:" << index
            << "with name:" << name
            << "read invalid value:" << _val;
            return false;
    }
    return true;
}

QString GetRadioConfig::get_cfg_name(int index)
{
    if (index <= 0 || index >= read_arr.count()) {
        qWarning() << "ERROR: request out-of-range";
        return "no-name";
    }

    QJsonObject _obj = read_arr.at(index).toObject();
    return _obj["name"].toString();
}

QString GetRadioConfig::get_cfg_id(int index)
{
    if (index <= 0 || index >= read_arr.count()) {
        qWarning() << "ERROR: request out-of-range";
        return "no-id";
    }

    QJsonObject _obj = read_arr.at(index).toObject();
    return _obj["id"].toString();
}

QString GetRadioConfig::get_cfg_value(int index)
{
    if (index <= 0 || index >= read_arr.count()) {
        qWarning() << "ERROR: request out-of-range";
        return "FF";
    }

    QJsonObject _obj = read_arr.at(index).toObject();
    QString _val = _obj["value"].toString();
    if (check_value(_val)) {
        return _val;
    } else {
        qWarning() << "ERROR: invalid value:" << _val;
        return "FF";
    }

}

void GetRadioConfig::set_cfg_value(int index, const QString& value)
{
    QString _name;
    QString _id;
    QString _value;

    if (!get_cfg_elem(index, _name, _id, _value)) {
        qWarning() << "ERROR: set_cfg_value(): error while fetching element data";
        return;
    }

    QJsonObject _obj;
    _obj.insert("name", _name);
    _obj.insert("id", _id);

    QString _val = value;
    _val = _val.trimmed();    // remove extra spaces
    if (_val.length() == 0) {
        qWarning() << "ERROR: length of value is zero!!!";
        _val = "FF";
    } else if (value.length() == 1) {
        qDebug() << "prefix with 0";
        _val = QString("0%1").arg(_val);
    }

    _obj.insert("value", _val);
    new_arr.push_back(QJsonValue(_obj));
}

void GetRadioConfig::test()
{
    qDebug() << __func__ << "load from:" << JSONFILE;
    if (!load_file(JSONFILE)) {
        qWarning() << "failed to load json file...";
        return;
    }
    const int total_count = 27;
    QString name;
    QString id;
    QString value;

    qDebug() << "write cfg with random numbers...";
    for (int i = 1; i <= total_count; ++i) {
        get_cfg_elem(i, name, id, value);
        // qDebug() << "name:" << name;
        // qDebug() << "id:" << id;
        // qDebug() << "value:" << value;

        set_cfg_value(i, get_rand_number());
    }

    QJsonObject new_obj;
    new_obj.insert("config", new_arr);
    QJsonDocument jdoc(new_obj);
    //qDebug() << jdoc.toJson();
    QString out_json_file = get_out_json_filename();
    qDebug() << "write json to:" << out_json_file;
    qDebug() << "write size:" << get_out_count();
    writeByteArrayToFile(jdoc.toJson(), out_json_file);
}

// using QFile to write
bool GetRadioConfig::writeByteArrayToFile(const QByteArray& arr, const QString& fn)
{
    QFile outFile(fn);
    if (!outFile.open(QIODevice::WriteOnly)) {
        qWarning() << "fail to write file:" << fn;
        return false;
    }
    if ( outFile.write(arr) == -1 ) {
        return false;
    }
    return true;
}

QStringList GetRadioConfig::travel_dir(const QString& path)
{
    QDir dir(path);

    QStringList currentFilter;
    currentFilter << "*.cfg" << "*.json";
    QStringList result;

    foreach (QString file, dir.entryList(currentFilter, QDir::Files | QDir::NoSymLinks)) {
        QFileInfo _info(dir, file);
        QString _fullfilepath = _info.filePath();
        //qDebug() << "_fullfilepath:" << _fullfilepath;
        result << _fullfilepath;
    }
    // sort string list
    if (!result.isEmpty()) {
        result.sort(Qt::CaseInsensitive);
    }

    return result;
    // foreach (QString subDir, dir.entryList(QDir::Dirs
    //                                        | QDir::NoDotAndDotDot | QDir::NoSymLinks)) {
    //     travel_dir(path + QDir::separator() + subDir);
    // }

}

void GetRadioConfig::test_dir()
{
    QStringList files = travel_dir("/tmp");
    qDebug() << "files:" << files;
}

void GetRadioConfig::browse_dir()
{
    file_list.clear();
    file_list = travel_dir(DEFAULT_CONFIG_DIR);
    qDebug() << "files:" << file_list;
}

void GetRadioConfig::read_all()
{
    init_new_arr();
    load_file(DEFAULT_CONFIG_FILE);
}

void GetRadioConfig::write_all()
{
    QJsonObject new_obj;
    new_obj.insert("config", new_arr);
    QJsonDocument jdoc(new_obj);
    //qDebug() << jdoc.toJson();
    QString out_json_file = get_out_json_filename();
    qDebug() << "write json to:" << out_json_file;
    qDebug() << "write size:" << get_read_count();
    writeByteArrayToFile(jdoc.toJson(), out_json_file);

}

bool GetRadioConfig::check_value(const QString& value)
{
    QRegularExpression regexp("[0-9A-Fa-f][0-9A-Fa-f]?");
    QRegularExpressionMatch match = regexp.match(value);
    return match.hasMatch();
}
