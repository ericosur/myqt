#ifndef __UTIL_DOM_H__
#define __UTIL_DOM_H__

#include <QDomDocument>
#include <QDomElement>
#include <QString>


class HandleSvg
{
public:
    static HandleSvg* _instance;
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

protected:
    HandleSvg();

    void init();
    void load_svg(const QString& fn, QDomDocument& doc);
    void export_doc_to_png(const QDomDocument& doc, const QString& ofn);

    void travel_tag(QDomElement& elem, const QString& tag, const QString& id,
        const QString& attr, const QString& val);


private:
    const QString base_fn = "../base.svg";
    const QString left_fn = "../left.svg";
    const QString right_fn = "../right.svg";

    QDomDocument base_doc;
    QDomDocument left_doc;
    QDomDocument right_doc;
};



#endif  // __UTIL_DOM_H__
