#ifndef __UTIL_DOM_H__
#define __UTIL_DOM_H__

#include <QDomDocument>
#include <QDomElement>
#include <QString>

#define SIZE_OF_CMDARRAY        12
#define BASE_APPLY_PNG          "/tmp/base_apply.png"
#define RIGHT_APPLY_PNG         "/tmp/right_apply.png"
#define LEFT_APPLY_PNG          "/tmp/left_apply.png"


class HandleSvg
{
public:
    static HandleSvg* getInstance();

    void test();
    void test_left();
    void test_right();

    void change_base_exit(int id, const QString& color);
    void export_base_png(const QString& ofn = "base.png");

    void change_left_phase(int id, const QString& color);
    void export_left_png(const QString& ofn = "left.png");

    void change_right_phase(int id, const QString& color);
    void export_right_png(const QString& ofn = "right.png");

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
    void dump_arr(int cmd_arr[SIZE_OF_CMDARRAY]);

private:
    // const QString base_fn = "../base.svg";
    // const QString left_fn = "../left.svg";
    // const QString right_fn = "../right.svg";
    const QString BASE_FN = ":/base.svg";
    const QString LEFT_FN = ":/left.svg";
    const QString RIGHT_FN = ":/right.svg";

    QDomDocument base_doc;
    QDomDocument left_doc;
    QDomDocument right_doc;

    int mCnt = 0;
};



#endif  // __UTIL_DOM_H__
