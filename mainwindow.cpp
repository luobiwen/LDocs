#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include<QMouseEvent>
#include<QPropertyAnimation>
#include<QGraphicsColorizeEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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
    if(watched == ui->toolButton_106){
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
{
    //QString filename=QFileDialog::getOpenFileName(this,"请选择一个文件","");
    //QUrl filename=QFileDialog::getOpenFileUrl(this,"请选择一个文件夹");
    QString filename="C:\\Users\\1\\Desktop\\TugeDocs\\mainw";
    QTreeWidgetItem * rootitem=new QTreeWidgetItem();
    if(filename.isEmpty())return;
    //else ui->stackedWidget->setCurrentWidget(ui->html);
    else filemanager->FiletoList(filename,rootitem);
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
    QString filename=QFileDialog::getOpenFileName(this,"请选择一个文件","","TXT(*.txt)");
    if(filename.isEmpty())return;
    else ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_108_pressed()
{
    QString filename=QFileDialog::getOpenFileName(this,"请选择一个文件","","TXT(*.txt)");
    if(filename.isEmpty())return;
    else ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_7_pressed()
{
    ui->stackedWidget->setCurrentWidget(ui->html);
}

