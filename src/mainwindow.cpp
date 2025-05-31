#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"myFileManager.h"
#include"myDSManager.h"
#include"myHelpDialog.h"
#include"myAboutDialog.h"
#include<QFileDialog>
#include<QMouseEvent>
#include<QPropertyAnimation>
#include<QGraphicsColorizeEffect>
#include<QDesktopServices>
//左侧工具栏悬停动画有点问题 curfile统一一下
//我发现所有的自定义按钮都是点了之后有点问题 都要改
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dsmanager = new myDSManager();
    dsmanager->sendRequest("你好");
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->start);
    installEventFiltersToAllWidgets();
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->toolButton_7->setIconSize(ui->toolButton_7->size());
    ui->pushButton_2->setGeometry(15,15,50,50);
    setIconColor(ui->toolButton_106,QColor(0, 170, 255));
    setIconColor(ui->toolButton_107,QColor(0,0, 0));
    setIconColor(ui->toolButton_108,QColor(0,0, 0));
    setIconColor(ui->toolButton_109,QColor(0,0, 0));
    setIconColor(ui->toolButton_2,QColor(0,0, 0));
    setIconColor(ui->toolButton_3,QColor(0,0, 0));
    setIconColor(ui->toolButton_12,QColor(255, 255, 255));
    setIconColor(ui->toolButton,QColor(255, 255, 255));
    setIconColor(ui->toolButton_101,QColor(255, 255, 255));
    setIconColor(ui->toolButton_102,QColor(255, 255, 255));
    setIconColor(ui->toolButton_103,QColor(255, 255, 255));
    setIconColor(ui->toolButton_132,QColor(255, 255, 255));
    filemanager = new myFileManager;
    ui->treeWidget->setHeaderHidden(true);  // 隐藏表头
    curfile="";
    ui->lineEdit_2->setReadOnly(true);
}
//设置图片动画
void MainWindow::setimagecartoon(QToolButton* button){

}

//设置图片滤镜
void MainWindow::setbackgroundimageeffect(QToolButton* button, const QColor& color,double r){
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(button);
    effect->setColor(color);  // 红色滤镜
    effect->setStrength(r);             // 70%强度
    button->setGraphicsEffect(effect);
}

//安装事件过滤器
void MainWindow::installEventFiltersToAllWidgets(){
    QList<QToolButton*> buttons = findChildren<QToolButton*>();
    foreach (QToolButton *button, buttons) {
        button->installEventFilter(this);
    }
    this->installEventFilter(this);
}
//实现事件过滤器
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched==ui->toolButton_157||watched == ui->toolButton_3||watched == ui->toolButton_2||watched == ui->toolButton_107||watched == ui->toolButton_108||watched == ui->toolButton_109) {
        filterButtonIconColor(qobject_cast<QToolButton*>(watched),QColor(0, 100, 255),QColor(0, 0, 0),event);
    }
    if(watched == ui->toolButton_12||watched == ui->toolButton_132||watched == ui->toolButton_101||watched == ui->toolButton_102||watched == ui->toolButton_103||watched == ui->toolButton_105||watched == ui->toolButton){
        filterButtonIconColor(qobject_cast<QToolButton*>(watched),QColor(0, 100, 255),QColor(255, 255, 255),event);
    }
    if(watched == ui->toolButton_106){//106第一次press了之后背景颜色不能变回来
        filterButtonIconColor(qobject_cast<QToolButton*>(watched),QColor(Qt::white),QColor(0, 170, 255),event);
    }
    if(watched == ui->toolButton_7||watched == ui->toolButton_8||watched == ui->toolButton_6){
        if (event->type() == QEvent::Enter) {
            setbackgroundimageeffect(qobject_cast<QToolButton*>(watched),QColor(0, 170, 255),0.7);
            return true;
        }
        else if (event->type() == QEvent::Leave) {
            setbackgroundimageeffect(qobject_cast<QToolButton*>(watched),QColor(77, 82, 147),0.1);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
//过滤器设置悬停效果
bool MainWindow::filterButtonIconColor(QToolButton* button, const QColor& color1,const QColor& color2,QEvent *event){
    if (event->type() == QEvent::Enter) {
        setIconColor(button,color1);
        return true;
    }
    else if (event->type() == QEvent::Leave) {
        setIconColor(button,color2);
        return true;
    }
    else{
        return true;
    }
}
//设置图标颜色
void MainWindow::setIconColor(QToolButton* button, const QColor& color) {
    QIcon icon = button->icon();
    QPixmap pixmap = icon.pixmap(button->iconSize());
    QPixmap coloredPixmap(pixmap.size());
    coloredPixmap.fill(color);
    coloredPixmap.setMask(pixmap.createMaskFromColor(Qt::transparent));
    button->setIcon(QIcon(coloredPixmap));
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->readme);
}


void MainWindow::on_toolButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->start);
}


void MainWindow::on_toolButton_101_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->issue);
}


void MainWindow::on_toolButton_102_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->api);
}


void MainWindow::on_toolButton_103_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->date);
}


void MainWindow::on_toolButton_132_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->help);
}


void MainWindow::on_toolButton_3_pressed()
{//filemanger肯定没问题的 测试url能过 那就是这里有点问题 新建要获取到当前的item 然后newfile
    //QString filename=QFileDialog::getOpenFileName(this,"请选择一个文件","");
    //QUrl filename=QFileDialog::getOpenFileUrl(this,"请选择一个文件夹");
    QString filename="C:/Users/1/Desktop/TugeDocs/mainw";
    curfile = filename;
    QTreeWidgetItem * rootitem=new QTreeWidgetItem(QStringList()<<"");
    ui->treeWidget->addTopLevelItem(rootitem);
    if(filename.isEmpty())return;
    //else ui->stackedWidget->setCurrentWidget(ui->html);
    else filemanager->FiletoList(filename,rootitem);
    return;
}

//标题鼠标事件
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=ui->widget_39->x();
    int y=ui->widget_39->y();
    int w=ui->widget_39->width();
    int h=ui->widget_39->height();
    //只能是鼠标左键移动和改变大小
    if((event->button() == Qt::LeftButton) //处于左键状态
        &&(event->x()>x&&event->x()<x+w)  //x坐标位置判定
        &&(event->y()>y&&event->y()<y+h)) //y坐标位置判定
    {
        m_leftMousePressed = true;  //标志位置为真
        //按下时鼠标左键时，窗口在屏幕中的坐标
        m_StartPoint = event->globalPos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口,由于取消了标题栏，因此需要自己实现拖动窗口功能
    if (m_leftMousePressed)
    {
        QPoint curPoint = event->globalPos();   //按住移动时的位置
        QPoint movePoint = curPoint - m_StartPoint; //与初始坐标做差，得位移
        //普通窗口
        QPoint mainWinPos = this->pos();
        //设置窗口的全局坐标
        this->move(mainWinPos.x() + movePoint.x(), mainWinPos.y() + movePoint.y());
        m_StartPoint = curPoint;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_leftMousePressed = false;//释放鼠标，标志位置为假
}



void MainWindow::on_toolButton_14_pressed()
{
    this->showMinimized();
}


void MainWindow::on_toolButton_15_pressed()
{
    this->close();
}


void MainWindow::on_toolButton_106_pressed()
{
    curfile=QFileDialog::getOpenFileName(this,"请选择一个文件","","TXT(*.txt)");
    if(curfile.isEmpty())return;
    else {
        ui->stackedWidget->setCurrentWidget(ui->html);
        filemanager->LoadFile(curfile,ui->textEdit_100);
        QFileInfo fileinfo(curfile);
        ui->lineEdit_2->setText(fileinfo.fileName());
    }
}


void MainWindow::on_toolButton_108_pressed()
{
    on_toolButton_106_pressed();
}

void MainWindow::on_toolButton_7_pressed()
{
    ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_2_pressed()
{
    QTreeWidgetItem * newitem=new QTreeWidgetItem(QStringList()<<"new");
    newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);
    ui->treeWidget->addTopLevelItem(newitem);
    QString path=curfile+myFileManager().getItemPath(ui->treeWidget->topLevelItem(0));
    myFileManager().NewFile(path,"newitem.txt");
}


void MainWindow::on_textEdit_100_textChanged()
{
    filemanager->EditFile(curfile,ui->textEdit_100);
}


void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    //filemanager->EditFileName(curfile,ui->lineEdit_2);
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    // QString cleanPath = QDir::cleanPath(a);
    // QUrl url = QUrl::fromLocalFile(cleanPath);
    // QUrl a=curfile+(myFileManager().getItemPath(item)).toString();
    //QDesktopServices::openUrl(url);
}


void MainWindow::on_toolButton_12_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}


void MainWindow::on_toolButton_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}

void MainWindow::on_toolButton_101_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}

void MainWindow::on_toolButton_102_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}

void MainWindow::on_toolButton_103_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}

void MainWindow::on_toolButton_132_pressed()
{
    ui->toolButton_12->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_101->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_102->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_103->setStyleSheet("QToolButton {border: none;background-color: rgb(77, 82, 147);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
    ui->toolButton_132->setStyleSheet("QToolButton {border: none;background-color: rgb(0, 0, 127);color: white;padding: 4px;font:bold 16px;border-top-left-radius:20px;border-bottom-left-radius:20px;}");
}


void MainWindow::on_pushButton_2_clicked()
{
    QString pic=QFileDialog::getOpenFileName(this,"请选择一个文件","","PNG(*.png);;JPG(*.jpg)");
    QString style=QString("QPushButton{border:1px solid;  rgb(77, 82, 147);border-radius:25px;    padding:0px 0px;  background-image: url(%1); background-repeat:no-reapeat;background-position:center;background-size:cover; color:white;	min-width:50px;min-height:50px;font:bold 18px;").arg(pic);
    ui->pushButton_2->setStyleSheet(style);
}


void MainWindow::on_toolButton_6_pressed()
{
    on_toolButton_104_pressed();
}



void MainWindow::on_toolButton_104_pressed()
{//dialog的菜单栏还得改
    HelpDialog *dialog = new HelpDialog(this);
    dialog->show();
}


void MainWindow::on_toolButton_105_pressed()
{
    AboutDialog *dialog = new AboutDialog(this);
    dialog->show();
}


void MainWindow::on_toolButton_107_pressed()
{
    curfile="";
    ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_110_pressed()
{
    AboutDialog *dialog = new AboutDialog(this);
    QObject::connect(ui->toolButton_110, &QToolButton::clicked, dialog, &AboutDialog::show);
}


void MainWindow::on_toolButton_157_pressed()
{
    //myFileManager().searchAndHighlightInTreeWidget(ui->lineEdit->text(), ui->treeWidget);
    //myFileManager().filterItems(ui->treeWidget->topLevelItem(0),ui->lineEdit->text());
}


void MainWindow::on_toolButton_109_pressed()
{
    QString outputfile=QFileDialog::getOpenFileName(this,"请选择导出地址","");

}


void MainWindow::on_toolButton_5_pressed()
{
    QString prompt = ui->textEdit_7->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_100;
    connect(dsmanager, &myDSManager::responseReceived,
            this, &MainWindow::onResponseReceived);
}

void MainWindow::onResponseReceived(const QString &text) {
    curtextedit->setHtml("<pre>" + text.toHtmlEscaped() + "</pre>"); // 将API响应显示到QTextEdit
}

void MainWindow::on_toolButton_4_pressed()
{
    QString prompt=ui->textEdit_6->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_5;
    connect(dsmanager, &myDSManager::responseReceived,
            this, &MainWindow::onResponseReceived);
}


void MainWindow::on_toolButton_11_pressed()
{
    QString prompt=ui->textEdit_19->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_20;
    connect(dsmanager, &myDSManager::responseReceived,
            this, &MainWindow::onResponseReceived);
}


void MainWindow::on_toolButton_8_pressed()
{
    QString prompt=ui->textEdit_13->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_14;
    connect(dsmanager, &myDSManager::responseReceived,
           this, &MainWindow::onResponseReceived);
}


void MainWindow::on_toolButton_9_pressed()
{
    QString prompt=ui->textEdit_15->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_16;
    connect(dsmanager, &myDSManager::responseReceived,
           this, &MainWindow::onResponseReceived);
}


void MainWindow::on_toolButton_10_pressed()
{
    QString prompt=ui->textEdit_17->toPlainText();
    dsmanager->sendRequest(prompt);
    curtextedit = ui->textEdit_18;
    connect(dsmanager, &myDSManager::responseReceived,
            this, &MainWindow::onResponseReceived);
}


void MainWindow::on_toolButton_113_pressed()
{

}


void MainWindow::on_toolButton_130_pressed()
{

}


void MainWindow::on_toolButton_155_pressed()
{

}


void MainWindow::on_toolButton_143_pressed()
{

}


void MainWindow::on_toolButton_147_pressed()
{

}


void MainWindow::on_toolButton_151_pressed()
{

}


void MainWindow::on_toolButton_114_pressed()
{
    on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_112_pressed()
{
    on_toolButton_106_pressed();
}


void MainWindow::on_toolButton_111_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_128_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_129_pressed()
{
     on_toolButton_106_pressed();
}

void MainWindow::on_toolButton_131_pressed()
{
     on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_153_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_154_pressed()
{
    on_toolButton_106_pressed();
}


void MainWindow::on_toolButton_156_pressed()
{
    on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_141_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_142_pressed()
{
     on_toolButton_106_pressed();
}


void MainWindow::on_toolButton_144_pressed()
{
    on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_145_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_146_pressed()
{
     on_toolButton_106_pressed();
}


void MainWindow::on_toolButton_148_pressed()
{
    on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_149_pressed()
{
    on_toolButton_7_pressed();
}


void MainWindow::on_toolButton_150_pressed()
{
    on_toolButton_106_pressed();
}


void MainWindow::on_toolButton_152_pressed()
{
    on_toolButton_105_pressed();
}


void MainWindow::on_toolButton_200_pressed()
{

}


void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

}



void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    qDebug()<<curfile+"/"+myFileManager().getItemPath(item);
    myFileManager().renameFile("C:\\Users\\1\\Desktop\\TugeDocs\\mainw\\new","ne");
    //myFileManager().renameFile(curfile+"/"+myFileManager().getItemPath(item),item->text(0));
}

