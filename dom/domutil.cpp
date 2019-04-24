/**
 * for base.svg, **polygon** __id__ from exit_00, exit_01, ..., to exit_11
 * for left.svg and right.svg, **path** __id__ from phase0, phase1, ..., to phase11
 */

#include "domutil.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QImage>
#include <QDebug>

#define DEFAULT_WIDTH       120
#define DEFAULT_HEIGHT      120

void travel_tag(QDomElement& elem, const QString& tag);

HandleSvg* HandleSvg::_instance = NULL;
HandleSvg* HandleSvg::getInstance()
{
    if (_instance == NULL) {
        _instance = new HandleSvg();
    }
    return _instance;
}

HandleSvg::HandleSvg()
{
    init();
}

void HandleSvg::init()
{
    load_svg(base_fn, base_doc);
    load_svg(right_fn, right_doc);
    load_svg(left_fn, left_doc);
}

void HandleSvg::test()
{
    change_base_exit(1, "red");
    change_base_exit(5, "lightyellow");
    change_base_exit(10, "limegreen");
    export_base_png("b1.png");

    change_base_exit(2, "red");
    change_base_exit(4, "lightyellow");
    change_base_exit(9, "limegreen");
    export_base_png("b2.png");

}

void HandleSvg::export_base_png(const QString& ofn)
{
    export_doc_to_png(base_doc, ofn);
    load_svg(base_fn, base_doc);
}

void HandleSvg::export_left_png(const QString& ofn)
{
    export_doc_to_png(left_doc, ofn);
    load_svg(left_fn, left_doc);
}

void HandleSvg::export_right_png(const QString& ofn)
{
    export_doc_to_png(right_doc, ofn);
    load_svg(right_fn, right_doc);
}

void HandleSvg::load_svg(const QString& fn, QDomDocument& doc)
{
    QFile file(fn);
    file.open(QIODevice::ReadOnly);
    QByteArray baData = file.readAll();

    // load svg contents to xml document and edit contents
    doc.setContent(baData);

    //QDomElement docElem = doc.documentElement();
}

void HandleSvg::export_doc_to_png(const QDomDocument& doc, const QString& ofn)
{
    // create svg renderer with edited contents
    QSvgRenderer svgRenderer(doc.toByteArray());

    QImage image(QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT), QImage::Format_ARGB32);
    QPainter painter;

    image.fill(Qt::transparent);
    painter.begin(&image);
    svgRenderer.render(&painter);
    painter.end();

    if (image.save(ofn)) {
        qDebug() << "[INFO] export image:" << ofn;
    } else {
        qDebug() << "[FAIL] failed to export" << ofn;
    }
}

void HandleSvg::change_base_exit(int id, const QString& color)
{
    QDomElement base_e = base_doc.documentElement();
    QString strid = QString::asprintf("exit_%02d", id);
    travel_tag(base_e, "polygon", strid, "fill", color);
}

void HandleSvg::travel_tag(QDomElement& elem, const QString& tag, const QString& id,
    const QString& attr, const QString& val)
{
    //qDebug() << "travel_tag:" <<  tag << id << attr << val;
    if (elem.tagName() == tag) {
        if (elem.attribute("id") == id) {
            elem.setAttribute(attr, val);
        }
        return;
    }
    QDomNode n = elem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            travel_tag(e, tag, id, attr, val);
        }
        n = n.nextSibling();
    }
}

#if 0

void HandleSvg::travel_tag(QDomElement& elem, const QString& tag, const QString& id,
    const QString& attr, const QString& val)
{
    qDebug() << "travel_tag:" <<  tag << id << attr << val;
    if (elem.tagName() == tag) {
        if (elem.attribute("id") == id) {
            elem.setAttribute(attr, val);
        }
        return;
    }
    QDomNode n = elem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            travel_tag(e, tag, id, attr, val);
        }
        n = n.nextSibling();
    }
}

void SetAttrRecur(QDomElement &elem, QString strtagname, QString strattr, QString strattrval);
void ChangeSVGColor(const QString& fn);


/*
https://stackoverflow.com/questions/15123544/change-the-color-of-an-svg-in-qt
 */
void ChangeSVGColor(const QString& fn)
{
    // open svg resource load contents to qbytearray
    QFile file(fn);
    file.open(QIODevice::ReadOnly);
    QByteArray baData = file.readAll();
    // load svg contents to xml document and edit contents
    QDomDocument doc;
    doc.setContent(baData);
    // recurivelly change color
    QDomElement docElem = doc.documentElement();
    //SetAttrRecur(docElem, "path", "fill", "pink");
    //travel_tag(docElem, "polygon");
}
#endif


#if 0
void SetAttrRecur(QDomElement& elem, QString strtagname, QString strattr, QString strattrval)
{
    // if it has the tagname then overwritte desired attribute
    if (elem.tagName().compare(strtagname) == 0) {
        elem.setAttribute(strattr, strattrval);
    }
/*
    // loop all children
    for (int i = 0; i < elem.childNodes().count(); i++) {
        if (!elem.childNodes().at(i).isElement()) {
            continue;
        }
        SetAttrRecur(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
    }
*/
    QDomNode n = elem.firstChild();
    while (!n.isNull()) {
        QDomElement e = n.toElement();
        if (!e.isNull()) {
            SetAttrRecur(e, strtagname, strattr, strattrval);
        }
        n = n.nextSibling();
    }

}
#endif
