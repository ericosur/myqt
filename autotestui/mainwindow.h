#ifndef __AUTOTEST_MAINWINDOW_H__
#define __AUTOTEST_MAINWINDOW_H__

#include <QItemSelectionModel>
#include <QJsonObject>
#include <QListView>
#include <QMainWindow>
#include <QMutex>
#include <QProcess>
#include <QPushButton>
#include <QStringListModel>
#include <QTimer>

class ReadJson;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* e);
    void runCommand(const QString& cmd);

    QString queryCommand(const QString& name);

    static const int MAX_CATEGORY = 18;
    static const int MAX_FUNCTION = 8;
    static const int COLDDOWN_INTERVAL = 250;

private slots:
    void categoryClicked(const QString& s);

    void slotStarted();
    void slotFinished(int i);
    void slotReadStdout();
    void slotReadStderr();
    void slotError(QProcess::ProcessError e);
    void slotState(QProcess::ProcessState s);

    void slotRun();
    void slotKill();
    void slotInfo();
    void slotAbout();

    void slotSelectionChanged();
    void sltTimeout();

signals:
    void sigRequestTerminated();
    void sigCleanUp();

private:
    void initEmptyButtons();
    void initButtonGroups();
    void initActionsConnections();
    void initListViewConnections();
    void setStyleSheet();

    QString composeString(const QString s, int i);
    void addline(const QString& s);
    void addlineColor(const QString& s, const QColor& c);
    void addlineY(const QString& s) {
        addlineColor(s, "yellow");
    }
    void addmsg(const QString& s) {
        addlineColor(s, "darkgray");
    }

    void showCurrentTime();
    // load autotestui config
    void loadConfig();
    void loadAutotestConfig();

    void hitAndRun();

private:
    // test functions
    void test();
    void testLocale();
    void testParse(const QString& s);
    //void testSplit();
    QList<QString> testSplit();
    void testTime();


private:
    Ui::MainWindow *ui = nullptr;
    QFont m_fixedfont;

    QPushButton *btnCategoryGroup[MAX_CATEGORY];

    QProcess *m_process = nullptr;
    QString m_stdout;
    QString m_stderr;
    int m_exitcode;

    QMap<QString, QString> name_cmd;
    QStringList cmds_to_run;
    QStringList cmds;

    QJsonObject jd;
    QString mAutotestConfig;
    QString mListWidgetStyleSheet;
    QString mTextEditStyleSheet;

    QMutex mutex;
    QTimer* runTimer = nullptr;
};

#endif // __AUTOTEST_MAINWINDOW_H__
