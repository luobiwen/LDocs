#ifndef MYHELPDIALOG_H
#define MYHELPDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class HelpDialog : public QDialog {
public:
    HelpDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("帮助文档");
        setMinimumSize(900, 600);

        // 创建控件
        QLabel *lblTitle = new QLabel("<h1><font color='white'>用户指南</font></h1>", this);
        lblTitle->setStyleSheet("border: none;");
        QTextEdit *textContent = new QTextEdit(this);
        textContent->setHtml(
            "<h2><font color='white'>1. 基本操作</font></h2>"
            "<p><font color='white'>这里是操作说明...</font></p>"
            "<h2><font color='white'>2. 常见问题</font></h2>"
            "<p><font color='white'>Q: 如何保存文件？<br>A: 点击菜单栏的“文件->保存”。</font></p>"
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

#endif // MYHELPDIALOG_H
