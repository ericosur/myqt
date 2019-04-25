#include "core.h"
#include "domutil.h"

#define TIMER_INTERVAL      1000
#define JSON_CONFIG         "/ssd/src/myqt/dom/config.json"

Core* Core::_instance = NULL;
Core* Core::getInstance()
{
    if (_instance == NULL) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
    qsrand((uint)QDateTime::currentMSecsSinceEpoch());

    test_timer = new QTimer(this);
    connect(test_timer, SIGNAL(timeout()), this, SLOT(sltTimeout()));
    test_timer->setSingleShot(true);
    test_timer->setInterval(TIMER_INTERVAL);
    test_timer->start();
}

void Core::sltTimeout()
{
    qDebug() << "sltTimeout";

    test_timer->setSingleShot(true);
    test_timer->setInterval(TIMER_INTERVAL);
    test_timer->start();

    int tmpNumber = 0;
    QString tmpDir;
    if (rj.loadFile(JSON_CONFIG)) {
        tmpNumber = rj.getInt("roundaboutExitNumber", 0);
        tmpDir = rj.getString("roundaboutExitDirections", "");
    }

    if ( (!exitDirection.isEmpty() && exitNumber >= 0) &&
        (tmpNumber == exitNumber && tmpDir == exitDirection)) {
        qDebug() << "not changed, exit...";
    } else {
        exitNumber = tmpNumber;
        exitDirection = tmpDir;
        qDebug() << "exitNumber:" << exitNumber << ","
            << "exitDirection:" << exitDirection;
        make_svg_command(exitDirection, exitNumber);
    }
}

void Core::make_svg_command(const QString& cmd, int nth)
{
    QStringList sl = cmd.split(",", QString::SkipEmptyParts);
    bool ok = false;
    int base_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int left_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int right_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool isLeft = false; // positive mean left, negative mean right
    bool isRight = false;
    HandleSvg* svg = HandleSvg::getInstance();
    QString ret;

    // exit number is the nth item from cmd string
    // for example, cmd = "0,3,5,9" and nth is 1
    // so exit number is 1st item from **cmd**

    int draw_exit_number = 0;
    if (nth == 0) {
        qDebug() << "[INFO] exitNumber is not roundabout";
    }
    if (nth > 0 && nth <= sl.size()) {
        draw_exit_number = sl[nth-1].toInt();
        if (draw_exit_number >= 0) {
            left_part_array[draw_exit_number] = 1;
            right_part_array[draw_exit_number] = 1;
            isLeft = true;
        } else {
            draw_exit_number = -draw_exit_number;
            right_part_array[draw_exit_number] = 1;
            isRight = true;
        }
        qDebug() << "[INFO] draw_exit_number:" << draw_exit_number;
        //ret = svg->apply_base(draw_exit_number);
        //setBasesvg(QString("file://%1").arg(ret));
    } else {
        qWarning() << "[FAIL] make_svg_command: nth OOB";
    }

    for (int i = 0 ; i < sl.size(); ++i) {
        int v = sl[i].toInt(&ok, 10);
        if (!ok) {
            qWarning() << "[FAIL] invalid numeric:" << sl[i];
            continue;
        }
        if (v == 0) {
            base_part_array[0] = 1;
        }
        int pos;
        if (v < 0) {
            pos = -v;
            if (pos > 0 && pos < 12)  { // 1 .. 11
                base_part_array[pos] = 1;
            }
            isRight = true;
        } else {
            pos = v;
            if (pos > 0 && pos < 12) {  // 1 .. 11
                base_part_array[pos] = 1;
            }
            isLeft = true;
        }
    }

    // base layer
    ret = svg->apply_base(base_part_array);
    setBasesvg(QString("file://%1").arg(ret));

    // exit layer
    if (isRight) {
        ret = svg->apply_right(right_part_array);
        setRightsvg(QString("file://%1").arg(ret));
        setOutsvg(QString("file://%1").arg(ret));
    } else if (isLeft) {
        ret = svg->apply_left(left_part_array);
        setLeftsvg(QString("file://%1").arg(ret));
        setOutsvg(QString("file://%1").arg(ret));
    } else {
        qWarning() << "[FAIL] nor left or right?";
    }
    //qDebug() << "[INFO] export image to" << ret;
    //return ret;
}

void test()
{
    HandleSvg* svg = HandleSvg::getInstance();
    svg->test();
}
