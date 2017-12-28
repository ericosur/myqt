#include <QtCore>
#include <QDebug>

#include "core.h"


// [in] input filename
//
// this function will read each lines from file and
// store into a QStringList
//
void test(const QString& input_file)
{
    QStringList stringList;
    QString fn;

    // check file existence
    if (QFile::exists(input_file)) {
        fn = input_file;
    } else {
        fn = QString("../%1").arg(input_file);
    }

    qDebug() << "read data from:" << fn;
    QFile data(fn);
    if (data.open(QFile::ReadOnly)) {
        QTextStream textStream(&data);
        while (true) {
            QString line = textStream.readLine();
            if (line.isNull()) {
                break;
            }
            else {
                stringList.append(line);
            }
        }
        qDebug() << "readLine finished, dump string list:" << endl
            << stringList;
    } else {
        qDebug() << "cannot open file";
    }
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    Core core;

    if ( core.read_setting() ) {
        QString fn = core.get_data_filename().c_str();
        //qDebug() << "try to read from:" << fn;
        test(fn);
    } else {
        qDebug() << "fail to locate data file";
    }

    return 0;
}
