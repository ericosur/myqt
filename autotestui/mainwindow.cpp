#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readjson.h"

#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>
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

#define AUTOTEST_CONFIG_PATH "autotest.json"
#define DEFAULT_BUFFER_SIZE 2048
#define VERSION "autotestui 2019-07-02"
#define TEST_STRING "1234567890123456789012345678901234567890123456789012345678901234567890"
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

    loadConfig();
    loadAutotestConfig();

    setStyleSheet();

    // setup buttons
    initListViewConnections();
    initActionsConnections();
    initEmptyButtons();
    initButtonGroups();

    // show some info
    addline(m_fixedfont.toString());
    showCurrentTime();

    //testLocal();
    //testSplit();
    //testTime();
    addline(QDir::currentPath() + QString("/autotestui"));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    addline(msg);
    msg = QString("UTC: %1").arg(QDateTime::currentDateTimeUtc().toString());
    addline(msg);
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
        //connect(button, SIGNAL(clicked()), signalMapperCategory, SLOT(map()));
        QString assignText = composeString("nullptr", i);
        if (i < jd_keys.size()) {
            assignText = jd_keys.at(i);
            button->setEnabled(true);
            button->setVisible(true);
        }
        button->setText(assignText);
        //signalMapperCategory->setMapping(button, assignText);

        connect(button, &QPushButton::clicked, [=] { categoryClicked(assignText); });
        //connect(button, &QPushButton::clicked, ui->listWidget, &QListWidget::clear);
    }

    // connect(signalMapperCategory, SIGNAL(mapped(QString)),
    //         this, SIGNAL(categoryClicked(QString)));

    categoryClicked(jd_keys.at(0));
}

void MainWindow::initActionsConnections()
{
    ui->btnRun->setEnabled(false);

    // other actions
    //connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearTextArea()));
    //connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    //connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(runLineCommand()));

    connect(ui->btnKill, SIGNAL(clicked(bool)), this, SLOT(slotKill()));
    connect(ui->btnRun, SIGNAL(clicked(bool)), this, SLOT(slotRunCommands()));
    connect(ui->btnInfo, SIGNAL(clicked(bool)), this, SLOT(slotInfo()));
    connect(ui->btnAbout, SIGNAL(clicked(bool)), this, SLOT(slotAbout()));
    connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(clearTextArea()));
    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(close()));
}

void MainWindow::initListViewConnections()
{
    qDebug() << __func__;
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this,
            &MainWindow::slotSelectionChanged);
}

void MainWindow::slotSelectionChanged()
{
    //qDebug() << __func__;

    QList<QListWidgetItem*> sel = ui->listWidget->selectedItems();
    //qDebug() << sel.size();
    cmds_to_run.clear();
    for (int i = 0; i < sel.size(); ++i) {
        QListWidgetItem* p = sel.at(i);
        QVariant v = p->data(Qt::DisplayRole);
        cmds_to_run << queryCommand(v.toString());
    }


    ui->btnRun->setEnabled(!cmds_to_run.empty());
}

// this SLOT will know which btnCategory## is clicked
void MainWindow::categoryClicked(const QString& s)
{
    if (s.isEmpty()) {
        qDebug() << "[ERROR] empty category button is pressed!";
        return;
    }

    ui->listWidget->clear();
    m_category = s;
    qDebug() << "execCategory() " << m_category;

    QJsonArray arr = jd[s].toArray();
    if (arr.empty()) {
        qDebug() << "[ERROR] array is empty";
        return;
    }

    //QStringList sl;
    for (int i = 0; i < arr.size(); i++) {
        QString name = arr[i].toObject()["name"].toString();
        QString cmd = arr[i].toObject()["cmd"].toString();
        name_cmd.insert(name, cmd);
        ui->listWidget->addItem(name);
        //sl << name;

        // addline(name);
        // addline(cmd);
    }

    //listModel.setStringList(sl);
    //selectModel.setModel(&listModel);
}

// void MainWindow::setAllFuncButtons(bool onOff)
// {
//     qDebug() << __func__ << onOff;
// }

QString MainWindow::composeString(const QString s, int i)
{
    QString res = s + QString::number(i);
    return res;
}

void MainWindow::initCategory()
{
}

void MainWindow::addline(const QString &s)
{
    ui->textEdit->append(s);
}

void MainWindow::clearTextArea()
{
    ui->textEdit->clear();
}

void MainWindow::runLineCommand()
{
//    QString cmd = ui->lineEdit->text();
//    if (cmd != "") {
//        addline(cmd);
//        runCommand(cmd);
//    }
}

void MainWindow::slotRunCommands()
{
    ui->btnRun->setEnabled(false);

    qDebug() << __func__ << "list all selected cmds ==========>>>";
    qDebug() << cmds_to_run;
    runAllCommands();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    addline("key(): " + QString::number(e->key(), 16));
    addline("nativescancode(): " + QString::number(e->nativeScanCode(), 16));
    addline("text(): "+ e->text());
}

void MainWindow::runAllCommands()
{
    if (cmds_to_run.empty()) {
        //qDebug() << "command waiting list is empty";
        ui->btnRun->setEnabled(true);
        return;
    }
    QString cc = cmds_to_run.takeFirst();
    runCommand(cc);
}

void MainWindow::runCommand(const QString& cmd)
{
    if (cmd.isEmpty()) {
        qDebug() << "cmd is null, skip...";
        return;
    }

    m_process = new QProcess(this);

    connect(m_process, SIGNAL(started()), this, SLOT(slotStarted()));
    connect(m_process, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadStdout()));
    connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(slotReadStderr()));
    connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(slotState(QProcess::ProcessState)));

    connect(this, SIGNAL(sigRequestTerminated()), m_process, SLOT(terminate()));
    connect(this, SIGNAL(sigCleanUp()), this, SLOT(slotCleanUp()));

#ifndef Q_OS_WIN
    QString append_cmd = QString("/bin/bash -c \"") + cmd + QString("\"");
#else
    QString append_cmd = QString("\"") + cmd + QString("\"");
#endif
    addline(QString("cmd: ") + cmd);
    m_process->start(append_cmd);
    ui->btnKill->setEnabled(true);
    ui->btnInfo->setEnabled(true);
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

    //addline(m_stdout);
    if (m_exitcode) {
        addline("Finished(): exit code != 0, exitcode = " + QString::number(m_exitcode));
        //addline(m_stderr);
    }

    //m_stdout = "";
    //m_stderr = "";
//    if (m_process) {
//        delete m_process;
//        m_process = nullptr;
//    }

    emit sigCleanUp();
}

void MainWindow::slotCleanUp()
{
    ui->btnKill->setEnabled(false);
    ui->btnInfo->setEnabled(false);

    runAllCommands();
}

void MainWindow::slotReadStdout()
{
    //qDebug() << "slotReadStdout";
    QString output = m_process->readAllStandardOutput();
    addline(output);
    //rasmus test
    testParse(output);
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
        str = QString("pid: ") + QString::number(m_process->processId());
        addline(str);
    }
    str = QString("autotestui pid: %1").arg(qApp->applicationPid());
    addline(str);
}

void MainWindow::slotAbout()
{
    addline(VERSION);
    QString build_datetime = QString("built at: ") + QString(__DATE__) + " " + QString(__TIME__);
    addline(build_datetime);
//    addline(QString("config: " + m_configpath));
    addline(TEST_STRING);
}

void MainWindow::testLocale()
{
    //qDebug() << "test()";
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
    }
#endif
}

QList<QString> MainWindow::testSplit()
{
    //QRegularExpression re("|");
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
