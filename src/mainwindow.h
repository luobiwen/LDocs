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

    void on_textEdit_100_textChanged();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_toolButton_12_pressed();

    void on_toolButton_pressed();

    void on_toolButton_101_pressed();

    void on_toolButton_102_pressed();

    void on_toolButton_103_pressed();

    void on_toolButton_132_pressed();

    void on_pushButton_2_clicked();

    void on_toolButton_6_pressed();

    void on_toolButton_104_pressed();

    void on_toolButton_105_pressed();

    void on_toolButton_107_pressed();

    void on_toolButton_110_pressed();

    void on_toolButton_157_pressed();

    void on_toolButton_109_pressed();

    void on_toolButton_5_pressed();

    void on_toolButton_4_pressed();

    void on_toolButton_11_pressed();

    void on_toolButton_8_pressed();

    void on_toolButton_9_pressed();

    void on_toolButton_10_pressed();
    void onResponseReceived(const QString &text);

    void on_toolButton_113_pressed();

    void on_toolButton_130_pressed();

    void on_toolButton_155_pressed();

    void on_toolButton_143_pressed();

    void on_toolButton_147_pressed();

    void on_toolButton_151_pressed();

    void on_toolButton_114_pressed();

    void on_toolButton_112_pressed();

    void on_toolButton_111_pressed();

    void on_toolButton_128_pressed();

    void on_toolButton_129_pressed();

    void on_toolButton_131_pressed();

    void on_toolButton_153_pressed();

    void on_toolButton_154_pressed();

    void on_toolButton_156_pressed();

    void on_toolButton_141_pressed();

    void on_toolButton_142_pressed();

    void on_toolButton_144_pressed();

    void on_toolButton_145_pressed();

    void on_toolButton_146_pressed();

    void on_toolButton_148_pressed();

    void on_toolButton_149_pressed();

    void on_toolButton_150_pressed();

    void on_toolButton_152_pressed();

    void on_toolButton_200_pressed();

private:
    Ui::MainWindow *ui;
    bool m_leftMousePressed;
    QPoint m_StartPoint;
    QPropertyAnimation *scaleAnim;
    myFileManager* filemanager;
    myDSManager* dsmanager;
    QString curfile;
    bool showLineNumbers;
    QTextEdit *curtextedit;
};
#endif // MAINWINDOW_H
