#include <QDataStream>
#include <QVariant>
#include <QMetaProperty>

#include "carvalue.h"
#include "trypath.h"

CarValue* CarValue::_instance = NULL;
CarValue* CarValue::getInstance()
{
    if (_instance == NULL) {
        _instance = new CarValue();
    }
    return _instance;
}

CarValue::CarValue()
{

}

void CarValue::dump()
{
/*
    qDebug() << "speed:" << mSpeed << "rpm:" << mRpm << "engineTemp:" << mEngineTemp
        << "maf:" << mMaf << "oxygen:" << mOxygen;
*/
    // using qt metaobject system
    for (int i = this->metaObject()->propertyOffset(); i < this->metaObject()->propertyCount(); ++i)
    {
        qDebug() << QString("%1:").arg(i)
            << this->metaObject()->property(i).name()
            << this->metaObject()->property(i).read(this);
    }
}

bool CarValue::loadJsonFile(const QString& fn)
{
    QStringList plist;
    QString result;

#ifndef USE_YOSETARGET
    plist << "./" << "../" << "/tmp/";
#else
    plist << "/var/run/" << "/tmp/";
#endif

    if (!QFile::exists(fn)) {
        if (searchFileFromList(plist, fn, result)) {
            // searched
        } else {
            qDebug() << "file not found after retrying";
            return false;
        }
    } else {
        // ok located
        result = fn;
    }

    qDebug() << "will open file from:" << result;

    ReadJson jn(result);
    if (!jn.loadFile()) {
        qWarning() << "failed to load json file";
        return false;
    }

    mSpeed = jn.getInt("speed", -1);
    mRpm = jn.getDouble("rpm", -1);
    mEngineTemp = jn.getInt("engine_temp", -1);
    mMaf = jn.getDouble("maf", -1);
    mOxygen = jn.getDouble("oxygen", -1);

    return true;
}

bool CarValue::load()
{
    bool ret = loadJsonFile(DEFAULT_JSONFILE);

    return ret;
}
