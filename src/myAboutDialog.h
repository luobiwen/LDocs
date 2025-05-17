#ifndef MYABOUTDIALOG_H
#define MYABOUTDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class AboutDialog : public QDialog {
public:
    AboutDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("帮助文档");
        setMinimumSize(900, 600);

        // 创建控件
        QLabel *lblTitle = new QLabel("<h1><font color='white'>关于我们</font></h1>", this);
        lblTitle->setStyleSheet("border: none;");
        QTextEdit *textContent = new QTextEdit(this);
        textContent->setHtml(
            "<h2><font color='white'>关于我们</font></h2>"
            "<p><font color='white'>这里是我们的说明...</font></p>"
            "<h2><font color='white'>联系方式</font></h2>"
            "<p><font color='white'>地址：<br>中山大学珠海校区</font></p>"
            );
        textContent->setReadOnly(true);
        textContent->setStyleSheet("border: none;");
        QPushButton *btnClose = new QPushButton("关闭", this);
        btnClose->setStyleSheet("border: none;color:white;min-height:40px;font:bold 18px;");
        connect(btnClose, &QPushButton::clicked, this, &QDialog::accept);

        // 布局
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(lblTitle);
        layout->addWidget(textContent);
        layout->addWidget(btnClose);
    }

};
#endif // MYABOUTDIALOG_H
