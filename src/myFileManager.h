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
#include <QRegularExpression>
#include <QMainWindow>
class myFileManager{
public:
    bool filterItems(QTreeWidgetItem*, const QString& );

    QJsonObject loadConfig(const QString &path);
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
    void NewFile(QString,QString);
    void LoadFile(QString,QTextEdit*);
    void EditFile(QString,QTextEdit*);
    void EditFileName(QString,QLineEdit*);
    QString getFileName(QTreeWidgetItem *, QString);


//ui传不过来
};
#endif // MYFILEMANAGER_H
