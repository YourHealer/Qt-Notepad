#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class noteWindow; }
QT_END_NAMESPACE

class noteWindow : public QMainWindow
{
    Q_OBJECT

public:
    //主要文本区
    QTextEdit *textEdit=new QTextEdit();
    //标签
    QLabel *labelText;
    QLabel* labelText2;
    QLabel* labelText3;
    QLabel* labelText4;
    //当前文件
    QString currentFile;
    //状态栏动作
    QAction *actionStatus;
    //状态栏
    QStatusBar *sBar;
    //判定
    bool showOrNot = true;

    noteWindow(QWidget *parent = nullptr);
    ~noteWindow();

public slots:
    void showlabelText();
    void showAbout();
    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotUndo();
    bool canBeSaveOrNot();
    bool slotSave();
    bool slotSaveAs();
    bool saveFile(QString);
    void slotNew();
    void setFileName(QString fileName);
    void slotOpen();
    void loadFile(QString fileName);
    void quitApp();
    void closeEvent(QCloseEvent *e);
    void slotNewWin();
    void slotDelete();
    void slotTime();
    void slotFont();
    void slotShowStatusOrNot();

private:
    Ui::noteWindow *ui;
};
#endif // NOTEWINDOW_H
