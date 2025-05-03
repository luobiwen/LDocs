#ifndef MYFILEMANAGER_H
#define MYFILEMANAGER_H
#include<QTreeWidget>
#include <QDir>
class myFileManager{
public:
    QFileInfoList FiletoList(QString,QTreeWidgetItem*);
};
#endif // MYFILEMANAGER_H
