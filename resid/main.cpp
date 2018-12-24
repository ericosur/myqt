#include <QCoreApplication>
#include <QDebug>
//#include <iostream>

#include "residutil.h"
#include "strdef.h"

//using namespace std;

void test_id(int id, const QString& strid)
{
    QStringList locs;

    locs << "ar_AE" << "en_US";

    QString str;
    foreach (const QString &loc, locs) {
        str = getStringByIntid(loc, id);
        qDebug() << "query:" << id << "return:" << str;
        str = getStringByStrid(loc, strid);
        qDebug() << "query:" << strid << "return:" << str;
    }

}

void test()
{
    qDebug() << getStringByStrid("es_MX", "stringid_plzconnectbt");
    qDebug() << getStringByStrid("ar_AE", "stringid_plzconnectbt");
#if 1
    qDebug() << getStringByIntid("ar_AE", STRING_MINSTRID-1);
    qDebug() << getStringByIntid("ar_AE", STRING_MINSTRID);
    qDebug() << getStringByIntid("ar_AE", STRING_MAXSTRID);
    qDebug() << getStringByIntid("ar_AE", STRING_MAXSTRID+  1);
    //findFileLocation("abc");
    test_id(9999999, "stringid_nosuchidexists");
    test_id(stringid_plzconnectbt, "stringid_plzconnectbt");
#endif
}

void test_all()
{

}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    test();

    return 0;
}
