#ifndef MYFILEMANAGER_H
#define MYFILEMANAGER_H
#include<QTreeWidget>
#include <QDir>
#include<QFile>
#include<QTextEdit>
#include<QLineEdit>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
class myFileManager{
public:
    QJsonObject loadConfig(const QString &path);
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
    void NewFile(QString,QString);
    void LoadFile(QString,QTextEdit*);
    void EditFile(QString,QTextEdit*);
    void EditFileName(QString,QLineEdit*);
};
#endif // MYFILEMANAGER_H
