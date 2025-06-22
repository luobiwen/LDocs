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
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include<QSaveFile>
class myFileManager{
public:
    QJsonObject loadConfig(const QString &path);
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
    void NewFile(QString,QString);
    void NewFolder(QString filepath);
    void LoadFile(QString,QTextEdit*);
    void EditFile(QString,QTextEdit*);
    QTreeWidgetItem* findAndHighlight(QTreeWidgetItem *item, const QString &keyword, bool firstMatchFound);
    void clearHighlights(QTreeWidget *treeWidget);
    bool renameFile(const QString &oldPath, const QString &newName);
    QString getItemPath(QTreeWidgetItem* item);
    QString adaptHtmlForQt(const QString &originalHtml);

//ui传不过来
};
#endif // MYFILEMANAGER_H
