#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QToolButton>
#include<QPropertyAnimation>
#include"myFileManager.h"
#include"myDSManager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPixmap coloredPixmap;
    QPixmap originalPixmap;
    void setIconColor(QToolButton* button, const QColor& color);
    void installEventFiltersToAllWidgets();
    bool filterButtonIconColor(QToolButton* button, const QColor& color1,const QColor& color2,QEvent *event);
private slots:
    bool eventFilter(QObject *watched, QEvent *event);

    void on_toolButton_clicked();

    void on_toolButton_12_clicked();

    void on_toolButton_101_clicked();

    void on_toolButton_102_clicked();

    void on_toolButton_103_clicked();

    void on_toolButton_132_clicked();

    void on_toolButton_3_pressed();

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    void on_toolButton_14_pressed();

    void on_toolButton_15_pressed();

    void on_toolButton_106_pressed();

    void on_toolButton_108_pressed();
    void setbackgroundimageeffect(QToolButton* button, const QColor& color,double r);

    void on_toolButton_7_pressed();
    void setimagecartoon(QToolButton* button);

    void on_toolButton_2_pressed();

    void on_textEdit_8_textChanged();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    bool m_leftMousePressed;
    QPoint m_StartPoint;
    QPropertyAnimation *scaleAnim;
    myFileManager* filemanager;
    myDSManager*dsmanager;
    QString curfile;
};
#endif // MAINWINDOW_H
