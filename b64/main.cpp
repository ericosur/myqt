#include <QCoreApplication>
#include <QString>
#include <QByteArray>
#include <QDebug>

QString showByteArray(const QByteArray& ba)
{
    QString resHex;
//    QString resDec;
    for (int i = 0; i < ba.size(); i++) {
        resHex.append( QString::number(ba.at(i), 16).rightJustified(2, '0') );
    }
//    resDec.append( QString::number(ba.at(i) );
    return resHex;
}

void test()
{
    QString str;;
    str.append(QChar(0x5f3f));
    //str.append(QChar(0x5f3a));
    qDebug() << str;

}


int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    //QCoreApplication a(argc, argv);
    //return a.exec();
    test();
    return 0;
}
