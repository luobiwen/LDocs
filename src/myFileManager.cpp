#include"myFileManager.h"

QFileInfoList myFileManager::FiletoList(QString dicpath,QTreeWidgetItem* rootitem){
    QDir dir(dicpath);
    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    foreach (QFileInfo var, file_list) {
        if(var.isDir()){
            QTreeWidgetItem* child=new QTreeWidgetItem(QStringList()<<var.fileName());
            rootitem->addChild(child);
            QFileInfoList child_file_list = FiletoList(var.absoluteFilePath(),child);
            file_list.append(child_file_list);
            file_list.append(var);
        }
        else if(var.isFile()){
            QTreeWidgetItem *childitem=new QTreeWidgetItem(QStringList() <<var.fileName());
            rootitem->addChild(childitem);
        }
    }
    return file_list;
}
