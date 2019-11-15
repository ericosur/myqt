#ifndef __LOAD_TEXT_H__
#define __LOAD_TEXT_H__

#include <QObject>
#include <QString>
#include <QMap>

class LoadText : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)

public:
    enum LangType {
        LangNull = 0,
        LangEn = 1000,
        LangAr,
        LangPt,
        LangFr,
        LangEs,
        LangRu,
        LangUk,
        LangJa,
    };

    Q_ENUMS(LangType)

public:
    explicit LoadText(QObject* parent = nullptr);
    ~LoadText() {}

    Q_INVOKABLE QString getTextWithId(LangType id);

    QString message();
    void setMessage(const QString& str);
    QString readTextfile(const QString& fn);

signals:
    void messageChanged();

private:
    QString m_text;
    QMap<LangType, QString> m_map = {
        {LangEn, "en_US"},
        {LangAr, "ar_AE"},
        {LangPt, "pt_PT"},
        {LangFr, "fr_FR"},
        {LangEs, "es_ES"},
        {LangRu, "ru_RU"},
        {LangUk, "uk_UK"},
        {LangJa, "ja_JP"},
    };
};

#endif  // __LOAD_TEXT_H__
