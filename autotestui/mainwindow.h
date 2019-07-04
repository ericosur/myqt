#ifndef __AUTOTEST_MAINWINDOW_H__
#define __AUTOTEST_MAINWINDOW_H__

#include <QItemDelegate>
#include <QJsonObject>
#include <QListView>
#include <QMainWindow>
#include <QProcess>
#include <QPushButton>
#include <QStringListModel>
#include <QItemSelectionModel>

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
    void runAllCommands();

    static const int MAX_CATEGORY = 18;
    static const int MAX_FUNCTION = 8;

private slots:
    void categoryClicked(const QString& s);
    void clearTextArea();
    void runLineCommand();

    void slotStarted();
    void slotFinished(int i);
    void slotReadStdout();
    void slotReadStderr();
    void slotError(QProcess::ProcessError e);
    void slotState(QProcess::ProcessState s);

    void slotRunCommands();
    void slotKill();
    void slotInfo();
    void slotCleanUp();
    void slotAbout();

    void slotSelectionChanged();

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
    void initCategory();
    void addline(const QString& s);
    //void setAllFuncButtons(bool onOff);
    void showCurrentTime();
    void testLocale();
    void testParse(const QString& s);
    //void testSplit();
    QList<QString> testSplit();
    void testTime();

    // load autotestui config
    void loadConfig();
    void loadAutotestConfig();

private:
    Ui::MainWindow *ui = nullptr;
    QFont m_fixedfont;

    QJsonObject jd;

    QPushButton *btnCategoryGroup[MAX_CATEGORY];
    QString m_category;

    QProcess *m_process = nullptr;
    QString m_stdout;
    QString m_stderr;
    int m_exitcode;

    //QItemDelegate itemDelegate;
    QMap<QString, QString> name_cmd;
    QStringList cmds_to_run;

    QString mAutotestConfig;
    QString mListWidgetStyleSheet;
    QString mTextEditStyleSheet;
};

#endif // __AUTOTEST_MAINWINDOW_H__
