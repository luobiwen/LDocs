#ifndef MYFILEMANAGER_H
#define MYFILEMANAGER_H
#include<QTreeWidget>
#include <QDir>
#include<QFile>
#include<QTextEdit>
#include<QLineEdit>
class myFileManager{
public:
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
    void WriteFile(QString);
    void LoadFile(QString,QTextEdit*);
    void EditFile(QString,QTextEdit*);
    void EditFileName(QString,QLineEdit*);
};
#endif // MYFILEMANAGER_H
