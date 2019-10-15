#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readjson.h"
#include "fileutil.h"

#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFontDatabase>
#include <QKeyEvent>

#include <QProcess>
#include <QRegularExpression>
#include <QThread>
#include <QDebug>

#ifdef USE_YOSETARGET
#define UI_CONFIG_PATH "/misc/ui.json"
#else
#define UI_CONFIG_PATH "ui.json"
#endif

#define DEFAULT_BUFFER_SIZE 2048
#define VERSION "autotestui 2019-07-12 keep selected"
#define TEST_STRING "1234567890123456789012345678901234567890123456789012345678901234567890"
#define EASY_HELP_TEXT "**Info** will show a list of selected commands"

#define AUTOTEST_CONFIG_PATH "autotest.json"
#define DEFAULT_LISTWIDGET_STYLESHEET \
            "color: black;" \
            "background-color: lightgray;" \
            "selection-color: black;" \
            "selection-background-color: steelblue;" \
            "font-size: 22px;"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mAutotestConfig(AUTOTEST_CONFIG_PATH),
    mListWidgetStyleSheet(DEFAULT_LISTWIDGET_STYLESHEET)
{
    ui->setupUi(this);

    // setup text edit
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, QColor(7, 7, 7));
    // background color for TextEdit
    ui->textEdit->setPalette(p);
    // text color for TextEdit
    ui->textEdit->setTextColor(QColor(255,255,255));
    m_fixedfont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ui->textEdit->setCurrentFont(m_fixedfont);
    ui->textEdit->setReadOnly(true);

    ui->btnTest->setEnabled(true);

    loadConfig();
    loadAutotestConfig();

    setStyleSheet();

    // setup buttons
    initListViewConnections();
    initActionsConnections();
    initEmptyButtons();
    initButtonGroups();

    // show some info
    addmsg(m_fixedfont.toString());
    showCurrentTime();

    //testLocal();
    //testSplit();
    //testTime();
    addmsg(QDir::currentPath() + QString("/autotestui"));

    runTimer = new QTimer(this);
    connect(runTimer, &QTimer::timeout, [=]{ sltTimeout(); });
    runTimer->setSingleShot(true);
    runTimer->setInterval(COLDDOWN_INTERVAL);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (runTimer != nullptr) {
        delete runTimer;
    }
}

void MainWindow::setStyleSheet()
{
    if (!mListWidgetStyleSheet.isEmpty()) {
        ui->listWidget->setStyleSheet(mListWidgetStyleSheet);
    }
    if (!mTextEditStyleSheet.isEmpty()) {
        ui->textEdit->setStyleSheet(mTextEditStyleSheet);
    }
}

void MainWindow::showCurrentTime()
{
    QString msg;
    msg = QString("localtime: %1").arg(QDateTime::currentDateTime().toString());
    addmsg(msg);
    // msg = QString("UTC: %1").arg(QDateTime::currentDateTimeUtc().toString());
    // addmsg(msg);
}

void MainWindow::initEmptyButtons()
{
#define INITCATEGORYBTN(n)    \
    btnCategoryGroup[n] = ui->btnCategory##n ; \
    btnCategoryGroup[n]->setEnabled(false); \
    btnCategoryGroup[n]->setVisible(false)

    INITCATEGORYBTN(0);
    INITCATEGORYBTN(1);
    INITCATEGORYBTN(2);
    INITCATEGORYBTN(3);
    INITCATEGORYBTN(4);
    INITCATEGORYBTN(5);
    INITCATEGORYBTN(6);
    INITCATEGORYBTN(7);
    INITCATEGORYBTN(8);
    INITCATEGORYBTN(9);
    INITCATEGORYBTN(10);
    INITCATEGORYBTN(11);
    INITCATEGORYBTN(12);
    INITCATEGORYBTN(13);
    INITCATEGORYBTN(14);
    INITCATEGORYBTN(15);
    INITCATEGORYBTN(16);
    INITCATEGORYBTN(17);

#undef INITCATEGORYBTN

}

void MainWindow::initButtonGroups()
{
    if (jd.isEmpty()) {
        qDebug() << "[ERROR] no config for autotest config";
        return;
    }
    QStringList jd_keys = jd.keys();
    for (int i = 0; i < MAX_CATEGORY; i++) {
        QPushButton* button = btnCategoryGroup[i];
        QString assignText = composeString("nullptr", i);
        if (i < jd_keys.size()) {
            assignText = jd_keys.at(i);
            button->setEnabled(true);
            button->setVisible(true);
        }
        button->setText(assignText);
        connect(button, &QPushButton::clicked, [=] { categoryClicked(assignText); });
    }

#ifndef USE_YOSETARGET
    categoryClicked("basic");
#else
    categoryClicked(jd_keys.at(0));
#endif
}

void MainWindow::initActionsConnections()
{
    ui->btnRun->setEnabled(false);

    // other actions
    //connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearTextArea()));
    //connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->btnKill, &QPushButton::clicked, [=]{ slotKill(); });
    connect(ui->btnRun, &QPushButton::clicked, [=]{ slotRun(); });
    connect(ui->btnInfo, &QPushButton::clicked, [=]{ slotInfo(); });
    connect(ui->btnAbout, &QPushButton::clicked, [=]{ slotAbout(); });
    connect(ui->btnQuit, &QPushButton::clicked, [=]{ close(); });
    connect(ui->btnClear, &QPushButton::clicked, [=]{ ui->textEdit->clear(); });
    connect(ui->btnTest, &QPushButton::clicked, [=]{ test(); });
    connect(this, SIGNAL(sigShowFile()), this, SLOT(slotShowFile()));
}

void MainWindow::initListViewConnections()
{
    qDebug() << __func__;
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this,
            &MainWindow::slotSelectionChanged);
    connect(ui->listWidget, &QListWidget::itemClicked, this,
            &MainWindow::slotItemClicked);
    connect(ui->listWidget, &QListWidget::itemPressed, this,
            &MainWindow::slotItemPressed);
}

void MainWindow::merge_run_list()
{
    for (QString ii: curr_cmds_to_run) {
        if (!total_cmds_to_run.contains(ii)) {
            total_cmds_to_run.append(ii);
        }
    }
}

void MainWindow::slotSelectionChanged()
{
#if 1
    bool doDebug = false;
    if (categoryState == csJustChanged) {
        if (doDebug)
            qDebug() << "===== skip this slotSelectionChanged =====";
        categoryState = csCurrentPage;
        return;
    }
    curr_cmds_to_run.clear();
    int cnt = ui->listWidget->count();
    for (int i = 0; i < cnt; ++i) {
        QListWidgetItem* p = ui->listWidget->item(i);
        QString name = p->data(Qt::DisplayRole).toString();
        QString cmd = queryCommand(name);
        //qDebug() << "check:" << name;
        if (p->isSelected()) {
            if (doDebug)
                qDebug() << "add" << cmd << " into curr list...";
            curr_cmds_to_run << cmd;
        } else {
            if (total_cmds_to_run.contains(cmd)) {
                if (doDebug)
                    qDebug() << "remove" << cmd << " from list...";
                total_cmds_to_run.removeOne(cmd);
            }
        }
    }
#else
    //qDebug() << __func__;
    QList<QListWidgetItem*> sel = ui->listWidget->selectedItems();
    //qDebug() << sel.size();
    curr_cmds_to_run.clear();
    for (int i = 0; i < sel.size(); ++i) {
        QListWidgetItem* p = sel.at(i);
        QVariant v = p->data(Qt::DisplayRole);
        curr_cmds_to_run << queryCommand(v.toString());
    }
#endif
    merge_run_list();
    ui->btnRun->setEnabled(!total_cmds_to_run.empty());
}

void MainWindow::slotItemClicked(QListWidgetItem* item)
{
    QVariant v = item->data(Qt::DisplayRole);
    QString name = v.toString();
    QString msg;
    if (item->isSelected()) {
        //msg = QString("item clicked: %1").arg(name);
        //addmsg(msg);
        if (name_readme.contains(name)) {
            QString fn = name_readme[name];
            addmsg(fn);
            if (!FileUtil::isFileExist(fn)) {
                addlineColor(QString("specified readme not found: %1").arg(fn), "deeppink");
                return;
            }
            byte_array.clear();
            if (readFileToByteArray(byte_array, fn)) {
                emit sigShowFile();
            }
        }
    }
}

void MainWindow::slotItemPressed(QListWidgetItem* item)
{
    Q_UNUSED(item);
    // QVariant v = item->data(Qt::DisplayRole);
    // if (item->isSelected()) {
    //     qDebug() << "item pressed:" << v.toString();
    // }
}

// this SLOT will know which btnCategory## is clicked
void MainWindow::categoryClicked(const QString& s)
{
    if (s.isEmpty()) {
        qDebug() << "[ERROR] empty category button is pressed!";
        return;
    }
    if (m_category == s) {
        qDebug() << "category NOT changed:" << m_category;
        categoryState = csCurrentPage;
        return;
    }

    qDebug() << "category changed" << m_category << "to" << s;
    if (m_category.isEmpty()) {
        categoryState = csFirstTime;
    } else {
        categoryState = csJustChanged;
    }
    m_category = s;
    name_cmd.clear();
    name_readme.clear();

    qDebug() << "total_cmds_to_run:" << total_cmds_to_run;

    // TODO: save current selected into inactive list
    merge_run_list();
    curr_cmds_to_run.clear();

    ui->listWidget->clear();
    //qDebug() << "execCategory() " << s;

    QJsonArray arr = jd[s].toArray();
    if (arr.empty()) {
        qDebug() << "[ERROR] json array is empty";
        return;
    }

    for (int i = 0; i < arr.size(); i++) {
        QString name = arr[i].toObject()["name"].toString();
        QString cmd = arr[i].toObject()["cmd"].toString();
        name_cmd.insert(name, cmd);

        QString readme = arr[i].toObject()["readme"].toString();
        if (!readme.isEmpty()) {
            name_readme.insert(name, readme);
        }

        QListWidgetItem* p = new QListWidgetItem(name);
        ui->listWidget->addItem(p);
        // restore selection state and its color
        bool isCmdExisted = total_cmds_to_run.contains(cmd);
        if (isCmdExisted) {
            if (curr_cmds_to_run.contains(cmd))
                qDebug() << cmd << "already contained";
            // restore list of current selected items
            curr_cmds_to_run << cmd;
            //p->setSelected(true);
            //p->setBackground(QColor("steelblue"));
            ui->listWidget->setCurrentItem(p, QItemSelectionModel::SelectCurrent);
        }
    }
}

QString MainWindow::composeString(const QString s, int i)
{
    QString res = s + QString::number(i);
    return res;
}

void MainWindow::addline(const QString& s)
{
    ui->textEdit->append(s);
}

void MainWindow::addlineColor(const QString& s, const QColor& c)
{
    QColor oldcolor = ui->textEdit->textColor();
    ui->textEdit->setTextColor(c);
    ui->textEdit->append(s);
    ui->textEdit->setTextColor(oldcolor);
}

void MainWindow::slotRun()
{
    ui->btnRun->setEnabled(false);

    qDebug() << __func__ << "=====>>>>>";
    //qDebug() << cmds_to_run;

    cmds = total_cmds_to_run;
    //qDebug() << "shoot timer!!!";
    runTimer->setInterval(COLDDOWN_INTERVAL);
    runTimer->start();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    addline("key(): " + QString::number(e->key(), 16));
    addline("nativescancode(): " + QString::number(e->nativeScanCode(), 16));
    addline("text(): "+ e->text());
}

void MainWindow::runCommand(const QString& cmd)
{
    if (cmd.isEmpty()) {
        qDebug() << "cmd is null, skip...";
        return;
    }

    //qDebug() << "lock!!!!!!!!";
    mutex.lock();
    m_process = new QProcess(this);

    //connect(m_process, SIGNAL(started()), this, SLOT(slotStarted()));
    connect(m_process, &QProcess::started, [=]{ slotStarted(); });
    connect(m_process, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStdout()));
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(slotReadStderr()));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(slotState(QProcess::ProcessState)));

    connect(this, SIGNAL(sigRequestTerminated()), m_process, SLOT(terminate()));

#ifndef Q_OS_WIN
    QString append_cmd = QString("/bin/bash -c \"") + cmd + QString("\"");
#else
    QString append_cmd = QString("\"") + cmd + QString("\"");
#endif
    qDebug() << "====> runCommand:" << cmd;
    addmsg(QString("cmd: ") + cmd);
    m_process->start(append_cmd);
    ui->btnKill->setEnabled(true);
    //m_process->waitForFinished(-1); // will wait forever until finished
}

void MainWindow::slotStarted()
{
    if (m_process) {
        qDebug() << "slotStarted() pid:" << QString::number(m_process->processId());
    }
}

void MainWindow::slotFinished(int i)
{
    qDebug() << "slotFinished(): " << i;
    m_exitcode = i;

    disconnect(m_process, SIGNAL(started()), this, SLOT(slotStarted()));
    disconnect(m_process, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
    disconnect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStdout()));
    disconnect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(slotReadStderr()));

    addmsg("finished, exitcode: " + QString::number(m_exitcode));
    //m_stdout = "";
    //m_stderr = "";
//    if (m_process) {
//        delete m_process;
//        m_process = nullptr;
//    }
    mutex.unlock();
    //qDebug() << "unlock!!!";

    ui->btnKill->setEnabled(false);

    //qDebug() << "shoot timer..........";
    runTimer->start();
}

void MainWindow::sltTimeout()
{
    //qDebug() << "=====" << __func__ << "=====";
    hitAndRun();
}

void MainWindow::hitAndRun()
{
    if (cmds.isEmpty()) {
        addlineColor("no more cmds to run...", "cyan");
        ui->btnRun->setEnabled(true);
    } else {
        QString this_cmd = cmds.takeFirst();
        //qDebug() << __func__ << "===== run:" << this_cmd;
        runCommand(this_cmd);
        return;
    }
}

void MainWindow::slotReadStdout()
{
    //qDebug() << "slotReadStdout";
    QString output = m_process->readAllStandardOutput();
    addline(output);
    //rasmus test
    //testParse(output);
}

void MainWindow::slotReadStderr()
{
    //qDebug() << "slotReadStderr";
    addline(m_process->readAllStandardError());
}

void MainWindow::slotError(QProcess::ProcessError e)
{
    switch (e) {
    case QProcess::FailedToStart:
        break;
    case QProcess::Crashed:
        break;
    case QProcess::Timedout:
        break;
    case QProcess::WriteError:
        break;
    case QProcess::ReadError:
        break;
    case QProcess::UnknownError:
        break;
    }
}

void MainWindow::slotState(QProcess::ProcessState s)
{
    switch (s) {
    case QProcess::NotRunning:
        //qDebug() << "not running...";
        //setAllFuncButtons(true);
        break;
    case QProcess::Starting:
        //qDebug() << "starting...";
        break;
    case QProcess::Running:
        //qDebug() << "running...";
        //setAllFuncButtons(false);
        break;
    }
}

void MainWindow::slotKill()
{
    if (m_process) {
        addline("button 'Kill' clicked");
        emit sigRequestTerminated();
    }
}

void MainWindow::slotInfo()
{
    //addline("info clicked");
    QString str;
    if (m_process) {
        quint64 pid = m_process->processId();
        if (pid) {
            str = QString("pid: ") + QString::number(pid);
            addmsg(str);
        }
    }
    str = QString("autotestui pid: %1").arg(qApp->applicationPid());
    addmsg(str);
    showCurrentTime();

    merge_run_list();
    if (total_cmds_to_run.isEmpty()) {
        addmsg("total command list is empty");
        return;
    }
    addmsg("==== total command list =====");
    for (QString s: total_cmds_to_run) {
        addmsg(s);
    }
}

void MainWindow::slotAbout()
{
    QString build_datetime = QString(VERSION) + QString(" at: ") + QString(__DATE__) + " " + QString(__TIME__);
    addmsg(build_datetime);
//    addline(QString("config: " + m_configpath));
    addmsg(TEST_STRING);
    addmsg(EASY_HELP_TEXT);
}

void MainWindow::test()
{
    addlineColor("test functions", "pink");
    testLocale();
    testParse("my ip is 192.168.100.199, what's yours?");
    testSplit();
}

void MainWindow::testLocale()
{
    addmsg("testLocale:");
    QLocale en = QLocale(QLocale::English, QLocale::UnitedKingdom);
    addline( en.dateTimeFormat(QLocale::ShortFormat) );
    addline( QDateTime::currentDateTime().toString(en.dateTimeFormat(QLocale::ShortFormat)) );

    QLocale us = QLocale(QLocale::English, QLocale::UnitedStates);
    addline( QDateTime::currentDateTime().toString(us.dateTimeFormat(QLocale::ShortFormat)) );

    QLocale pt = QLocale(QLocale::Portuguese, QLocale::Brazil);
    //addline( pt.dateTimeFormat() );
    addline( QDateTime::currentDateTime().toString(pt.dateTimeFormat(QLocale::ShortFormat)) );
}

void MainWindow::testParse(const QString& str)
{
    addmsg("testParse" + str);
#if 1
    QRegularExpression re("(\\d+\\.\\d+\\.\\d+\\.\\d+)");
    QRegularExpressionMatchIterator i = re.globalMatch(str);
    //qDebug() << "str:" << str;
    //QStringList words;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word1 = match.captured(1);
        //words << word;
        //qDebug() << "word1:" << word1;
        addline(word1);
    }
#endif
}

QList<QString> MainWindow::testSplit()
{
    addmsg("testSplit:");
    QString input = "mp3|mp4|mpg|wav|avi";
    QStringList filterlist = input.split("|");
    QList<QString> result;

    for (int i = 0; i < filterlist.size(); ++i) {
        result.append(filterlist.at(i));
        addline(filterlist.at(i));
    }
    return result;
}

void MainWindow::testTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    addline( QString("time_t: ") + QString::number(dt.toTime_t()) );
}

QString MainWindow::queryCommand(const QString& name)
{
    if (name.isEmpty()) {
        qDebug() << "fail to lookup:" << name;
        return QString();
    }

    return name_cmd.value(name);
}

void MainWindow::loadConfig()
{
    ReadJson r;
    addline(QString("try to load: %1").arg(UI_CONFIG_PATH));
    if (!r.loadFile(UI_CONFIG_PATH)) {
        addline("ui.json not applied");
        return;
    }
    addline(r.getString("caption", "no caption"));
    QString autotest = r.getString("autotest", AUTOTEST_CONFIG_PATH);
    mAutotestConfig = autotest;
    mListWidgetStyleSheet = r.getString("listwidget", DEFAULT_LISTWIDGET_STYLESHEET);
    mTextEditStyleSheet = r.getString("textedit", "");
}

void MainWindow::loadAutotestConfig()
{
    ReadJson j;
    addline(QString("%1: %2").arg(__func__).arg(mAutotestConfig));
    if (!j.loadFile(mAutotestConfig)) {
        jd = QJsonObject();
        addline("and failed...");
    } else {
        jd = j.getJobject();
        //qDebug() << jd;
    }
}

bool MainWindow::readFileToByteArray(QByteArray& arr, const QString& fn)
{
    QFile inFile(fn);
    if (!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "fail to read file:" << fn;
        return false;
    }
    arr = inFile.readAll();
    return true;
}

void MainWindow::slotShowFile()
{
    addline(byte_array.data());
}
