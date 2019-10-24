#include "core.h"
#include "domutil.h"

Core* Core::_instance = nullptr;
Core* Core::getInstance()
{
    if (_instance == nullptr) {
        _instance = new Core();
    }
    return _instance;
}

Core::Core()
{
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

// go right side of lane
bool Core::isGoRightLane(const QStringList& sl)
{
    bool ret = false;
    bool needAppendZero = false;
    for (int i = 0; i < sl.size(); i ++) {
        int d = sl[i].toInt();
        if (d == 0) {
            needAppendZero = true;
            continue;
        }
        if (d > 0) {
            ret = true;
        } else {
            d = -d;
        }
        exits.append(d);
    }
    if (needAppendZero) {
        exits.append(0);
    }

    // qDebug() << "isGoRightLane: exits:" << exits;
    // qDebug() << "does go right side?" << ret;
    return ret;
}

void Core::make_svg_command(const QString& cmd, int nth)
{
    int base_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int left_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int right_part_array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    QStringList sl = cmd.split(",", QString::SkipEmptyParts);
    exits.clear();
    bool goRight = isGoRightLane(sl);
    HandleSvg* svg = HandleSvg::getInstance();

    // exit number is the nth item from cmd string
    // for example, cmd = "0,3,5,9" and nth is 1
    // so exit number is 1st item from **cmd**
    // qDebug() << "nth =" << nth;
    // qDebug() << "sorted exits:" << exits;
    int draw_exit_number = 0;
    if (nth == 0) {
        qDebug() << "[INFO] exitNumber is not roundabout";
    }
    if (nth > 0 && nth <= exits.size()) {
        int t = exits[nth - 1];
        if (goRight) {
            right_part_array[t] = 1;
            left_part_array[t] = 1;
        } else {
            left_part_array[t] = 1;
        }
        qDebug() << "[INFO] draw_exit_number:" << draw_exit_number;
        //ret = svg->apply_base(draw_exit_number);
        //setBasesvg(QString("file://%1").arg(ret));
    } else {
        qWarning() << "[FAIL] make_svg_command: nth OOB";
    }

    for (int i = 0 ; i < exits.size(); ++i) {
        int pos = exits[i];
        base_part_array[pos] = 1;
    }

    // base layer
    QString ret = svg->apply_base(base_part_array);
    setBasesvg(QString("file://%1").arg(ret));

    // exit layer
    if (goRight) {
        ret = svg->apply_right(right_part_array);
        setRightsvg(QString("file://%1").arg(ret));
        setOutsvg(QString("file://%1").arg(ret));
    } else {
        ret = svg->apply_left(left_part_array);
        setLeftsvg(QString("file://%1").arg(ret));
        setOutsvg(QString("file://%1").arg(ret));
    }
    //qDebug() << "[INFO] export image to" << ret;
    //return ret;
}

void test()
{
    HandleSvg* svg = HandleSvg::getInstance();
    svg->test();
}
