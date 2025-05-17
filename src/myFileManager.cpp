#include"myFileManager.h"

QFileInfoList myFileManager::FiletoList(QString dicpath,QTreeWidgetItem* rootitem){
    QDir dir(dicpath);
    QDir dir_file(dicpath);    
    dir_file.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);        
    dir_file.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list_file = dir_file.entryInfoList();
    foreach (QFileInfo var, list_file) {
        QString name2=var.fileName();
        QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<<name2);
        child->setCheckState(1, Qt::Checked);
        child->setText(0,name2);
        rootitem->addChild(child);
    }
    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);  
    foreach(QFileInfo var,folder_list){
        QString namepath = var.absoluteFilePath();   
        QFileInfo folderinfo= var;
        QString name=folderinfo.fileName();      //获取目录名
        QTreeWidgetItem* childroot = new QTreeWidgetItem(QStringList()<<name);
        childroot->setCheckState(1, Qt::Checked);
        childroot->setText(0,name);
        rootitem->addChild(childroot);
        QFileInfoList child_file_list = FiletoList(namepath,childroot);          //进行递归
        file_list.append(child_file_list);
        file_list.append(var);
    }
    return file_list;
}

//获取list节点路径
QString myFileManager::getFileName(QTreeWidgetItem *pItem, QString currentrootpath)
{
    QTreeWidgetItem *pHeadItem = pItem;
    QString file_path;
    file_path = pItem->text(0);
    QTreeWidgetItem* pParentItem = pItem->parent();
    while (pParentItem!=nullptr && pParentItem!=pHeadItem) {
        file_path = pParentItem->text(0) + "\\" + file_path;
        pParentItem = pParentItem->parent();
    }
    file_path = currentrootpath + "\\" + file_path;
    return file_path;
}

void myFileManager::NewFile(QString filepath,QString filename){
    QString fullPath = filepath + "/" + filename;
    QFile file(fullPath);
}

void myFileManager::LoadFile(QString filepath,QTextEdit* textedit){
    if(filepath.isEmpty())return;
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly|QIODevice::WriteOnly | QIODevice::Text)) {
        QByteArray array=file.readAll();
        textedit->setPlainText(QString(array));
        file.close();
    }
    else textedit->setPlainText("无法打开文件");
    return;
}

void myFileManager::EditFile(QString filepath,QTextEdit* textedit){
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly|QIODevice::WriteOnly | QIODevice::Text)) {
        QByteArray array=textedit->toPlainText().toUtf8();
        file.write(array);
        file.close();
    }
    else textedit->setPlainText("无法编辑文件");
}

void myFileManager::EditFileName(QString filepath,QLineEdit*lineedit){//filename逻辑有问题
    QFile file(filepath);
    QFileInfo fileInfo(file);
    QString path = fileInfo.dir().absolutePath();
    file.rename(filepath);
}

QJsonObject myFileManager::loadConfig(const QString &path) {
    QFile file(path);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());    
    return doc.object();
}

//search逻辑没写完
bool myFileManager::RecluserFindItem(QTreeWidgetItem* pFItem, QRegularExpression regExp){
    myFileManager myfilemanager;
    QTreeWidget treewidget;
    bool rethidden = true;
    if (pFItem == NULL)
    {
        return rethidden;
    }

    int rowcount = 0;
    for (int c = rowcount - 1; c >= 0; c--)
    {
        QTreeWidgetItem* childItem = pFItem->child(1);
        if (childItem != NULL)
        {
            if (regExp.isValid())
            {
                RecluserFindItem(childItem, regExp);
                rethidden = false;
            }
            else
            {
                bool childret = RecluserFindItem(childItem, regExp);
                if (childret == false)
                {
                    rethidden = false;
                }
                QString strName = childItem->data(0,Qt::UserRole).toMap().value("name").toString();
                if (strName.contains(regExp) || childret == false)
                {
                    //找到
                    rethidden = false;
                }
                else
                {
                    //未找到
                }
            }
        }

    }
    return rethidden;
}
void myFileManager::RootItemSearch(QString strText)
{
    myFileManager myfilemanager;
    QTreeWidget treewidget;
    QRegularExpression regExp(strText);
    for (int i = 0; i < treewidget.columnCount(); i++)
    {
        QTreeWidgetItem* topitem =treewidget.topLevelItem(0);
        bool iret = myfilemanager.RecluserFindItem(topitem, regExp);

        QString strName = topitem->text(0);
        if (strName.contains(regExp) || iret == false)
        {
            //找到
        }
        else
        {
           //没找到
        }
    }
}
//使用案例QJsonObject config = loadConfig(":/config.json");
//QString encryptedToken = config["encrypted_token"].toString();
