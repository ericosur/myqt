#ifndef __UTIL_DOM_H__
#define __UTIL_DOM_H__

#include <QDomDocument>
#include <QDomElement>
#include <QString>

class HandleSvg
{
private:
    static const int SIZE_OF_CMDARRAY = 12;
    static const int DEFAULT_WIDTH = 120;
    static const int DEFAULT_HEIGHT = 120;

public:
    static HandleSvg* getInstance();

    void test();
    void test_left();
    void test_right();

    void change_base_exit(int id, const QString& color);
    void export_base_png(const QString& ofn);

    void change_left_phase(int id, const QString& color);
    void export_left_png(const QString& ofn);

    void change_right_phase(int id, const QString& color);
    void export_right_png(const QString& ofn);

    QString apply_base(int cmd_arr[SIZE_OF_CMDARRAY]);
    QString apply_right(int cmd_arr[SIZE_OF_CMDARRAY]);
    QString apply_left(int cmd_arr[SIZE_OF_CMDARRAY]);

protected:
    static HandleSvg* _instance;
    HandleSvg();

    void init();
    void load_svg(const QString& fn, QDomDocument& doc);
    void export_doc_to_png(const QDomDocument& doc, const QString& ofn);

    void travel_tag(QDomElement& elem, const QString& tag, const QString& id,
        const QString& attr, const QString& val);

    QString compose_filename(const QString& prefix);
    void dump_arr(const QString& msg, int cmd_arr[SIZE_OF_CMDARRAY]);

private:
    // to read svg file in the resource
    const QString BASE_FN = ":/res/base.svg";
    const QString LEFT_FN = ":/res/left.svg";
    const QString RIGHT_FN = ":/res/right.svg";
    const QString DISPLAY_COLOR = "#EA971E";

    QDomDocument base_doc;
    QDomDocument left_doc;
    QDomDocument right_doc;

    int mCnt = 0;
};



#endif  // __UTIL_DOM_H__
