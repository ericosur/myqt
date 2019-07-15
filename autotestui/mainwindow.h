#ifndef __AUTOTEST_MAINWINDOW_H__
#define __AUTOTEST_MAINWINDOW_H__

#include <QByteArray>
#include <QItemSelectionModel>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QListWidget>
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

    enum kCategoryState {
        csNone,
        csFirstTime,
        csJustChanged,
        csCurrentPage
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* e);
    void runCommand(const QString& cmd);

    static bool readFileToByteArray(QByteArray& arr, const QString& fn);

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
    void slotItemClicked(QListWidgetItem* item);
    void slotItemPressed(QListWidgetItem* item);
    void sltTimeout();

    void slotShowFile();

signals:
    void sigRequestTerminated();
    void sigCleanUp();
    void sigShowFile();

private:
    void initEmptyButtons();
    void initButtonGroups();
    void initActionsConnections();
    void initListViewConnections();
    void setStyleSheet();

    QString queryCommand(const QString& name);
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
    void testLocale();
    void testParse(const QString& s);
    //void testSplit();
    QList<QString> testSplit();
    void testTime();

    // load autotestui config
    void loadConfig();
    void loadAutotestConfig();

    void hitAndRun();
    void merge_run_list();


private:
    Ui::MainWindow *ui = nullptr;
    QFont m_fixedfont;

    QPushButton *btnCategoryGroup[MAX_CATEGORY];
    QString m_category;

    QProcess *m_process = nullptr;
    QString m_stdout;
    QString m_stderr;
    int m_exitcode;

    QMap<QString, QString> name_cmd;
    QMap<QString, QString> name_readme;

    kCategoryState categoryState = csNone;
    QStringList total_cmds_to_run;  // total cmds to run
    QStringList inactive_cmds_to_run;
    QStringList curr_cmds_to_run;   // cmds to run for current page
    QStringList cmds;   // temp, for runtime

    QJsonObject jd;
    QString mAutotestConfig;
    QString mListWidgetStyleSheet;
    QString mTextEditStyleSheet;

    QMutex mutex;
    QTimer* runTimer = nullptr;

    QByteArray byte_array;
};

#endif // __AUTOTEST_MAINWINDOW_H__
