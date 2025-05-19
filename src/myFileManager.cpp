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
    if(filepath.isEmpty())return;
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
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());    
    return doc.object();
}

// 递归过滤函数
bool myFileManager::filterItems(QTreeWidgetItem* item, const QString& keyword) {
    //搜索是能搜了 但是没有展示搜到的内容
    bool childMatch = false;
    qDebug()<<"跑到了";
    if(!item)return false;
    // 递归检查所有子项
    for (int i = 0; i < item->childCount(); ++i) {
        childMatch |= filterItems(item->child(i), keyword);
    }
    // 检查当前项是否匹配（以第0列为例）
    bool selfMatch = item->text(0).contains(keyword, Qt::CaseInsensitive);
    // 判断是否显示该项
    bool showItem = selfMatch || childMatch;
    item->setHidden(!showItem);
    // 如果匹配，确保父项展开
    if (showItem && item->parent()) {
        item->parent()->setExpanded(true);
    }
    return showItem;
}
//使用案例QJsonObject config = loadConfig(":/config.json");
//QString encryptedToken = config["encrypted_token"].toString();
