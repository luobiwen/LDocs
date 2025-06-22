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
#include<QStandardPaths>
#include <QPageSize>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include<QFontDatabase>
//左侧工具栏悬停动画有点问题
//我发现所有的自定义按钮都是点了之后有点问题 都要改
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dsmanager = new myDSManager();
    dsmanager->sendRequest("你好");
    ui->setupUi(this);//ui初始化
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
    ui->treeWidget->header()->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::ResizeMode::ResizeToContents);
    ui->treeWidget->header()->setStretchLastSection(false);
    ui->treeWidget->setAutoScroll(true);
    orifile="";
    isModified = false;
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
    if(watched == ui->toolButton_7||watched == ui->toolButton_200||watched == ui->toolButton_6){
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
    ui->stackedWidget->setCurrentWidget(ui->statistics);
}


void MainWindow::on_toolButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->start);
}


void MainWindow::on_toolButton_101_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_102_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->api);
}


void MainWindow::on_toolButton_103_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->notification);
}


void MainWindow::on_toolButton_132_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->help);
}


void MainWindow::on_toolButton_3_pressed()
{
    QUrl filename1=QFileDialog::getExistingDirectory(this,"请选择一个文件夹");
    curfile = filename1.toString();
    if(curfile!="")ui->treeWidget->clear();
    QTreeWidgetItem * rootitem=new QTreeWidgetItem(QStringList()<<"");
    ui->treeWidget->addTopLevelItem(rootitem);
    if(curfile.isEmpty())return;
    //else ui->stackedWidget->setCurrentWidget(ui->html);
    else filemanager->FiletoList(curfile,rootitem);
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
    // 获取当前选中项
    QTreeWidgetItem *selectedItem = ui->treeWidget->currentItem();
    if (!selectedItem) {
        // 没有选中项，添加到根目录
        myFileManager().NewFile(curfile, "newitem");
        QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "newitem");
        newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
        ui->treeWidget->addTopLevelItem(newItem);
        return;
    }
    // 获取选中项对应的完整路径
    QString itemPath = curfile + myFileManager().getItemPath(selectedItem);
    QFileInfo info(itemPath);
    QString targetDir;
    if (info.isDir()) {
        // 如果是目录，直接在该目录下创建新文件
        targetDir = itemPath;
    } else {
        // 如果是文件，取其所在目录
        targetDir = info.path();
    }
    // 创建新文件
    myFileManager().NewFile(targetDir, "newitem");
    // 创建新节点
    QTreeWidgetItem *newItem = new QTreeWidgetItem(QStringList() << "newitem");
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    // 添加节点
    if (info.isDir()) {
        // 选中的是目录，添加为子节点
        selectedItem->addChild(newItem);
        selectedItem->setExpanded(true);
    } else {
        // 选中的是文件，添加为同级节点
        if (selectedItem->parent()) {
            selectedItem->parent()->addChild(newItem);
        } else {
            ui->treeWidget->addTopLevelItem(newItem);
        }
    }
}

// 文本变化时只标记修改状态，不保存
void MainWindow::on_textEdit_100_textChanged()
{
    // 标记文件已被修改
    isModified = true;
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->stackedWidget->setCurrentWidget(ui->html);
    QString fileName = item->text(0);
    // 删除文件后缀（最后一个点之后的部分）
    int dotIndex = fileName.lastIndexOf('.');
    if (dotIndex != -1) {
        fileName = fileName.left(dotIndex);
    }
    ui->lineEdit_2->setText(fileName);
    QString newOrifile = curfile + myFileManager().getItemPath(item);
    QFileInfo fileInfo(newOrifile);
    // 检查当前文件是否有未保存的修改
    if(isModified && !orifile.isEmpty() && QFileInfo(orifile).isFile()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "未保存的更改",
                                      "当前文件有未保存的更改。是否保存？",
                                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if(reply == QMessageBox::Save) {
            saveCurrentFile();
        } else if(reply == QMessageBox::Cancel) {
            return;
        }
    }
    if(fileInfo.isFile()) {
        // 处理文件
        if(orifile != newOrifile) {
            QSignalBlocker blocker(ui->textEdit_100);
            orifile = newOrifile;
            myFileManager().LoadFile(orifile, ui->textEdit_100);
            isModified = false;
        }
    } else if(fileInfo.isDir()) {
        // 处理目录
        orifile = ""; // 清除当前文件路径
        isModified = false;
    } else {
        ui->textEdit_100->setHtml("<pre>错误: 路径无效或不存在</pre>");
        orifile = "";
        isModified = false;
    }
}

void MainWindow::saveCurrentFile()
{
    if(orifile.isEmpty()) {
        QMessageBox::warning(this, "保存失败", "没有打开的文件");
        return;
    }
    QFileInfo fileInfo(orifile);
    if(!fileInfo.isFile()) {
        QMessageBox::warning(this, "保存失败", "当前项目不是文件: " + orifile);
        return;
    }
    filemanager->EditFile(orifile, ui->textEdit_100);
    // 重置修改状态
    isModified = false;
    // 显示保存成功提示
    QMessageBox::information(this, "保存成功", "文件已保存: " + orifile);
}

// 键盘事件处理 - 捕获 Ctrl+S
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 检查是否按下 Ctrl+S
    if ((event->modifiers() & Qt::ControlModifier) && (event->key() == Qt::Key_S)) {
        saveCurrentFile();
        event->accept(); // 标记事件已处理
        return;
    }
    // 调用基类处理其他按键
    QMainWindow::keyPressEvent(event);
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
    on_toolButton_2_pressed();
    ui->stackedWidget->setCurrentWidget(ui->html);
}


void MainWindow::on_toolButton_110_pressed()
{
    AboutDialog *dialog = new AboutDialog(this);
    QObject::connect(ui->toolButton_110, &QToolButton::clicked, dialog, &AboutDialog::show);
}


void MainWindow::on_toolButton_157_pressed()
{
    myFileManager().clearHighlights(ui->treeWidget);
    myFileManager().findAndHighlight(ui->treeWidget->topLevelItem(0),ui->lineEdit->text(),false);
}


void MainWindow::on_toolButton_109_pressed()
{
    // 获取保存路径 - 使用更可靠的方法
    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString defaultName = ui->lineEdit_2->text().trimmed().isEmpty() ?
                              "未命名文档" : ui->lineEdit_2->text().trimmed();
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "导出PDF",
        defaultDir + "/" + defaultName + ".pdf",
        "PDF文件 (*.pdf)"
        );
    if (filePath.isEmpty()) return;
    // 确保文件扩展名正确
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";
    }
    // 检查文件路径是否有效
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.absoluteDir();
    // 检查目录是否存在
    if (!dir.exists()) {
        QMessageBox::critical(this, "错误", "目录不存在: " + dir.absolutePath());
        return;
    }
    // 检查目录是否可写
    if (!dir.isReadable()) {
        QMessageBox::critical(this, "错误", "目录不可读: " + dir.absolutePath());
        return;
    }
    // 尝试创建临时文件测试写权限
    QString testFilePath = filePath + ".test";
    QFile testFile(testFilePath);
    if (!testFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "错误",
                              QString("无法写入文件: %1\n错误: %2")
                                  .arg(testFilePath)
                                  .arg(testFile.errorString()));
        return;
    }
    testFile.write("test");
    testFile.close();
    QFile::remove(testFilePath);
    // 创建PDF写入器
    QPdfWriter pdfWriter(filePath);
    // 设置PDF版本（兼容性）
    pdfWriter.setPdfVersion(QPagedPaintDevice::PdfVersion_1_6);
    // 设置页面属性
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30)); // 单位是点(1/72英寸)
    // 设置标题和创建者信息
    QString title = ui->lineEdit_2->text().trimmed();
    if (title.isEmpty()) {
        title = "未命名文档";
    }
    pdfWriter.setTitle(title);
    pdfWriter.setCreator("luobiwen PDF导出工具");
    // 创建绘图器 - 使用更安全的方式
    QPainter painter;
    if (!painter.begin(&pdfWriter)) {
        QString errorMsg = "无法初始化PDF绘制器\n";
        errorMsg += "可能原因:\n";
        errorMsg += "- 文件路径无效或不可写\n";
        errorMsg += "- 系统权限问题\n";
        errorMsg += "- Qt PDF模块配置错误\n";
        errorMsg += "路径: " + filePath;

        QMessageBox::critical(this, "错误", errorMsg);
        return;
    }
    qDebug() << "成功初始化PDF绘制器";
    // 获取页面尺寸
    const int pageWidth = pdfWriter.width();
    const int pageHeight = pdfWriter.height();
    qDebug() << "页面尺寸:" << pageWidth << "x" << pageHeight;
    // 使用默认字体避免问题
    QFont defaultFont = QApplication::font();
    // 设置标题字体
    QFont titleFont = defaultFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    // 绘制标题
    painter.setPen(Qt::black);
    painter.drawText(0, 50, title);
    // 准备内容
    QString content = ui->textEdit_100->toPlainText();
    if (content.isEmpty()) {
        content = "（无内容）";
    }
    qDebug() << "内容长度:" << content.length();
    // 设置内容字体
    QFont contentFont = defaultFont;
    contentFont.setPointSize(150);
    painter.setFont(contentFont);
    // 创建QTextDocument处理文本布局
    QTextDocument textDoc;
    textDoc.setDefaultFont(contentFont);
    textDoc.setPlainText(content);
    // 设置文本区域
    int topMargin = 80; // 标题区域高度
    QRect contentRect(50, topMargin, pageWidth - 100, pageHeight - topMargin);
    qDebug() << "内容区域:" << contentRect;
    // 绘制文本背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));
    painter.drawRect(contentRect);
    painter.setPen(Qt::black);
    // 绘制文本
    textDoc.setTextWidth(contentRect.width());
    painter.save();
    painter.translate(contentRect.topLeft());
    // 实际绘制文本
    painter.setPen(Qt::black);
    textDoc.drawContents(&painter);
    painter.restore();
    // 结束绘制
    painter.end();
    qDebug() << "PDF文件创建成功:" << filePath;
    // 检查文件是否创建成功
    if (QFileInfo::exists(filePath) && QFileInfo(filePath).size() > 0) {
        // 尝试打开PDF
        if (QDesktopServices::openUrl(QUrl::fromLocalFile(filePath))) {
            QMessageBox::information(this, "导出成功", "PDF文件已成功导出并打开:\n" + filePath);
        } else {
            QMessageBox::information(this, "导出成功", "PDF文件已成功导出:\n" + filePath);
        }
    } else {
        QMessageBox::critical(this, "错误", "PDF文件创建失败，请检查路径和权限");
    }
}

void MainWindow::on_toolButton_115_pressed()
{

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
    on_toolButton_109_pressed();
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
    orifile=curfile+"/"+myFileManager().getItemPath(item);
    item->setData(0, Qt::UserRole, orifile);
}



void MainWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    qDebug()<<item->text(0);
    // 获取存储的原始路径
    QString oldPath = item->data(0, Qt::UserRole).toString();
    qDebug()<<oldPath;
    // 防止空路径或错误触发
    if (oldPath.isEmpty()) return;
    // 获取新名称
    QString newName = item->text(0);
    // 执行重命名
    bool success = myFileManager().renameFile(oldPath, newName);
    if (success) {
        // 更新路径存储（可选）
        QFileInfo newInfo(oldPath);
        newInfo.setFile(newInfo.dir(), newName);
        item->setData(0, Qt::UserRole, newInfo.absoluteFilePath());
    } else {
        // 恢复原名（避免显示错误名称）
        QSignalBlocker blocker(ui->treeWidget); // 阻塞信号
        item->setText(0, QFileInfo(oldPath).fileName());
    }
}

