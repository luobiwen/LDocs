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
#include<QMessageBox>

class myFileManager{
public:
    bool filterItems(QTreeWidgetItem*, const QString& );
    QJsonObject loadConfig(const QString &path);
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
    void NewFile(QString,QString);
    void NewFolder(QString filepath);
    void LoadFile(QString,QTextEdit*);
    void EditFile(QString,QTextEdit*);
    QTreeWidgetItem* findAndHighlight(QTreeWidgetItem *item, const QString &keyword, bool &firstMatchFound);
    void clearHighlights(QTreeWidget *treeWidget);
    void renameFile(const QString , const QString );
    QString getItemPath(QTreeWidgetItem* item);

//ui传不过来
};
#endif // MYFILEMANAGER_H
