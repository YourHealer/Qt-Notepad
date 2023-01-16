#include "notewindow.h"
#include "ui_notewindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QDockWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include <QTextDocument>
#include <QDateTime>
#include <QDebug>
#include <QFontDialog>

noteWindow::noteWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::noteWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("*新建文本文档.txt - 记事本");

//菜单栏
    QMenuBar *mBar=this->menuBar();
//菜单项
    QMenu *menuFile=mBar->addMenu("文件(F)");
    QMenu *menuEdit=mBar->addMenu("编辑(E)");
    QMenu *menuOperate=mBar->addMenu("格式(O)");
    QMenu *menuVisit=mBar->addMenu("查看(V)");
    QMenu *menuHelp=mBar->addMenu("帮助(H)");
//菜单动作
    //新建
    QAction *actionNew=menuFile->addAction("新建(N)");
    //设置快捷键
    actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    //信号与槽连接
    connect(actionNew,&QAction::triggered,this,&noteWindow::slotNew);

    //新窗口
    QAction *actionNewWin=menuFile->addAction("新窗口(W)");
    //设置快捷键
    actionNewWin->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT+ Qt::Key_N));
    //信号与槽连接
    connect(actionNewWin,&QAction::triggered,this,&noteWindow::slotNewWin);

    //打开
    QAction *actionOpen=menuFile->addAction("打开(O)...");
    //设置快捷键
    actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    //信号与槽连接
    connect(actionOpen,&QAction::triggered,this,&noteWindow::slotOpen);

    //保存
    QAction *actionSave=menuFile->addAction("保存(S)");
    //设置快捷键
    actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    //信号与槽连接
    connect(actionSave,&QAction::triggered,this,&noteWindow::slotSave);

    //另存为
    QAction *actionSaveNew=menuFile->addAction("另存为(A)...");
    //设置快捷键
    actionSaveNew->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT +Qt::Key_S));
    //信号与槽连接
    connect(actionSaveNew,&QAction::triggered,this,&noteWindow::slotSaveAs);

    //分割线
    menuFile->addSeparator();

    //页面设置
    menuFile->addAction("页面设置(U)...");

    //打印
    QAction *actionPrint = menuFile->addAction("打印(P)...");
    //设置快捷键
    actionPrint->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));

    //分割线
    menuFile->addSeparator();

    //退出
    QAction *actionQuit=menuFile->addAction("退出(X)");
    //设置快捷键
    actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    //信号与槽连接
    connect(actionQuit,&QAction::triggered,this,&noteWindow::quitApp);

//编辑
    //撤销
    QAction *actionZre=menuEdit->addAction("撤销(Z)");
    //设置快捷键
    actionZre->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    //信号与槽连接
    connect(actionZre,&QAction::triggered,this,&noteWindow::slotUndo);

    //分割线
    menuEdit->addSeparator();

    //剪切
    QAction *actionX=menuEdit->addAction("剪切(X)");
    //设置快捷键
    actionX->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    //信号与槽连接
    connect(actionX,&QAction::triggered,this,&noteWindow::slotCut);

    //复制
    QAction *actionC=menuEdit->addAction("复制(C)");
    //设置快捷键
    actionC->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    //信号与槽连接
    connect(actionC,&QAction::triggered,this,&noteWindow::slotCopy);

    //粘贴
    QAction *actionV=menuEdit->addAction("粘贴(V)");
    //设置快捷键
    actionV->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    //信号与槽连接
    connect(actionV,&QAction::triggered,this,&noteWindow::slotPaste);

    //删除
    QAction *actionL=menuEdit->addAction("删除(L)");
    //设置快捷键
    actionL->setShortcut(QKeySequence(Qt::Key_Delete));
    //信号与槽连接
    connect(actionL,&QAction::triggered,this,&noteWindow::slotDelete);

    //分割线
    menuEdit->addSeparator();

    //使用Bing搜索
    QAction *actionBing=menuEdit->addAction("使用Bing搜索...");
    //设置快捷键
    actionBing->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));

    //查找
    QAction *actionF=menuEdit->addAction("查找(F)...");
    //设置快捷键
    actionF->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));

    //查找下一个
    QAction *actionLatter=menuEdit->addAction("查找下一个(N)");
    //设置快捷键
    actionLatter->setShortcut(QKeySequence(Qt::Key_F3));

    //查找上一个
    QAction *actionFormer=menuEdit->addAction("查找上一个(V)");
    //设置快捷键
    actionFormer->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F3));

    //替换
    QAction *actionH=menuEdit->addAction("替换(H)...");
    //设置快捷键
    actionH->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));

    //转到
    QAction *actionG=menuEdit->addAction("转到(G)...");
    //设置快捷键
    actionG->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));

    //分割线
    menuEdit->addSeparator();

    //全选
    QAction *actionAll=menuEdit->addAction("全选(A)");
    //设置快捷键
    actionAll->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));

    //时间/日期
    QAction *actionTime=menuEdit->addAction("时间/日期(D)");
    //设置快捷键
    actionTime->setShortcut(QKeySequence(Qt::Key_F5));
    //信号与槽连接
    connect(actionTime,&QAction::triggered,this,&noteWindow::slotTime);

//格式
    //自动换行
    menuOperate->addAction("自动换行(W)");

    //字体
    QAction *actionFont=menuOperate->addAction("字体(F)...");
    //信号与槽连接
    connect(actionFont,&QAction::triggered,this,&noteWindow::slotFont);

//查看
    //缩放
    menuVisit->addAction("缩放(Z)");

    //状态栏
    actionStatus = menuVisit->addAction("• 状态栏");
    //信号与槽连接
    connect(actionStatus,&QAction::triggered,this,&noteWindow::slotShowStatusOrNot);

 //帮助
    //查看帮助
    menuHelp->addAction("查看帮助(H)");

    //发送反馈
    menuHelp->addAction("发送反馈(F)");

    //分割线
    menuHelp->addSeparator();

    //关于记事本
    QAction *actionAbout=menuHelp->addAction("关于记事本(A)");
    //信号与槽连接
    connect(actionAbout,&QAction::triggered,this,&noteWindow::showAbout);

 //文本编辑框
    //设置默认字体为宋体10号字
    textEdit->setFont(QFont("微软雅黑", 12));
    //设置文本区域为整个窗口的中央部件
    setCentralWidget(textEdit);

//状态栏
    sBar=this->statusBar();
    //编辑标签labelText
    labelText = new QLabel();
    labelText->setText("第1行，第1列");

    //添加标签labelText2
    labelText2 = new QLabel();
    labelText2->setText("100%   ");

    //添加标签labelText3
    labelText3 = new QLabel();
    labelText3->setText("Windows(CRLF)  ");

    //添加标签labelText4
    labelText4 = new QLabel();
    labelText4->setText("UTF-8  ");

    //显示标签
    if (true == showOrNot){
        sBar->addWidget(labelText);
        sBar->addWidget(labelText2);
        sBar->addWidget(labelText3);
        sBar->addWidget(labelText4);
    }

    //信号与槽连接
    connect(textEdit,&QTextEdit::cursorPositionChanged,this,&noteWindow::showlabelText);
}

noteWindow::~noteWindow()
{
    delete ui;
}

void noteWindow::showlabelText(){
    //获得鼠标光标
    QTextCursor textCursor = textEdit->textCursor();
    //行数
    int rowNum = textCursor.blockNumber();
    //列数
    int colNum = textCursor.columnNumber();
    //显示在Label上
    labelText->setText(tr("第%1行,第%2列").arg(rowNum+1).arg(colNum+1));
}

void noteWindow::showAbout()
{
    //利用对话框
   QMessageBox::about(this,"About NotePad","This notepad is improved by Shi Yabin.\n");
}

void noteWindow::slotCut(){
    textEdit->cut();
}

void noteWindow::slotCopy(){
    textEdit->copy();
}

void noteWindow::slotPaste(){
    textEdit->paste();
}

void noteWindow::slotUndo(){
    textEdit->undo();
}

bool noteWindow::canBeSaveOrNot(){
    //判断文件是否被修改
    if(textEdit->document()->isModified()){
        QMessageBox::StandardButtons result = QMessageBox::warning(this,"Waring","你想将更改保存吗?",
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        //取消
        if(QMessageBox::Cancel == result){
            return false;
        }
        //保存
        if(QMessageBox::Save == result){
            return slotSave();
        }
        //不保存
        if(QMessageBox::Discard == result){
            return true;
        }
    }
    return true;
}

bool noteWindow::slotSave(){
    if(currentFile.isEmpty()){
        return slotSaveAs();
    } else{
        return saveFile(currentFile);
        }
}

bool noteWindow::slotSaveAs(){
    QString fileName =QFileDialog::getSaveFileName(this,tr("Save As"),
                                "/home",tr("Text Files (*.txt)"));
    if(fileName.isEmpty()){
        return false;
    }else{
        return saveFile(fileName);
    }
}

bool noteWindow::saveFile(QString fileName){
    QFile* file = new QFile(fileName);
    if(false == file->open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this,
                              "critical",
                              "cannot write file"
                              );
        return false;
    }else{
        QTextStream out(file);
        out<<textEdit->toPlainText();
        file->setFileName(fileName);
        return true;
    }
}

void noteWindow::slotNew(){
    if(canBeSaveOrNot()){
        textEdit->clear();
        setFileName("");
    }
}

void noteWindow::setFileName(QString fileName){
    currentFile = fileName;
    textEdit->document()->setModified(false);
    this->setWindowModified(false);
    fileName.isEmpty() ? this->setWindowFilePath("new.txt") : this->setWindowFilePath(fileName);
}

void noteWindow::slotOpen(){
    if(canBeSaveOrNot()){
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

//加载文件
void noteWindow::loadFile(QString fileName){
    QFile* file = new QFile(fileName);
    if(false == file->open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this,
                              "critical",
                              "cannot read file"
                              );
    }else{
        QTextStream in(file);
        textEdit->setText(in.readAll());
        setFileName(fileName);
    }
}

void noteWindow::quitApp(){
    if(canBeSaveOrNot()){
        //关闭所有窗口
        qApp->closeAllWindows();
    }
}

void noteWindow::closeEvent(QCloseEvent *e){
    if(canBeSaveOrNot()){
        e->accept();
    }else{
       e->ignore();//忽略，直接关闭
    }
}

void noteWindow::slotNewWin()
{
    //创建新的窗口
    noteWindow *pNewWin = new noteWindow(this);
    pNewWin->show();
}

void noteWindow::slotDelete()
{
    //得到当前text的光标
    QTextCursor cursor=textEdit->textCursor();
    //如果有选中则取消，以免受受影响
       if(cursor.hasSelection())
           cursor.clearSelection();
       //删除前一个字符
       cursor.deletePreviousChar();
       textEdit->setTextCursor(cursor);
}

void noteWindow::slotTime()
{
    QString str;
    QDateTime time = QDateTime::currentDateTime();
    str = time.toString("yyyy-MM-dd hh:mm:ss");
    //qDebug() << str ;
    textEdit->append(str);
}

void noteWindow::slotFont()
{
    //获取当前用户设置的字体样式
        QFont getFont(bool *ok, const QFont &initial, QWidget *parent = Q_NULLPTR, const QString &title = QString());
        QFont getFont(bool *ok, QWidget *parent = Q_NULLPTR);

        bool bFlag = true;
        QFont font = QFontDialog::getFont(&bFlag);
        //修改字体
        textEdit->setFont(QFont(font.family(), font.pointSize(),font.bold(), font.italic()));
        //打印字体信息
        qDebug("当前选择的字体是[%s]-是否加粗[%d]-是否倾斜[%d]-字号[%d]", font.family().toUtf8().data(), font.bold(), font.italic(), font.pointSize());
}

void noteWindow::slotShowStatusOrNot()
{
    //触发时修改showOrNot状态
    if(true == showOrNot){
        showOrNot = false;
        actionStatus->setText("状态栏");
    }else{
        showOrNot = true;
        actionStatus->setText("• 状态栏");
    }

    //判定当前状态
    if (false == showOrNot){
        sBar->removeWidget(labelText);
        sBar->removeWidget(labelText2);
        sBar->removeWidget(labelText3);
        sBar->removeWidget(labelText4);
    }else{
        //编辑标签labelText
        labelText = new QLabel();
        labelText->setText("第1行，第1列");

        //添加标签labelText2
        labelText2 = new QLabel();
        labelText2->setText("100%   ");

        //添加标签labelText3
        labelText3 = new QLabel();
        labelText3->setText("Windows(CRLF)  ");

        //添加标签labelText4
        labelText4 = new QLabel();
        labelText4->setText("UTF-8  ");

        sBar->addWidget(labelText);
        sBar->addWidget(labelText2);
        sBar->addWidget(labelText3);
        sBar->addWidget(labelText4);
    }
}
