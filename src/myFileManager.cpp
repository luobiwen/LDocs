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
        child->setFlags(child->flags() | Qt::ItemIsEditable);
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
        childroot->setFlags(childroot->flags() | Qt::ItemIsEditable);
        rootitem->addChild(childroot);
        QFileInfoList child_file_list = FiletoList(namepath,childroot);          //进行递归
        file_list.append(child_file_list);
        file_list.append(var);
    }
    return file_list;
}

void myFileManager::NewFile(QString filepath,QString filename){
    //QString fullPath = filepath.toString() + "/" + filename;
    qDebug()<<"新文件"+filepath+ "/"+filename;
    QFile file(filepath+ "/"+filename);
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QString temp = "这是一条测试文本"; // 写入内容
        // 将内容写入文件
        QTextStream out(&file);
        out << temp;
        file.close();
    }
}

void myFileManager::NewFolder(QString filepath){
    QDir().mkdir(filepath);
}

void myFileManager::LoadFile(QString filepath,QTextEdit* textedit){//loadfile还有问题
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

void myFileManager::clearHighlights(QTreeWidget *treeWidget)
{
    QTreeWidgetItemIterator it(treeWidget);
    while (*it) {
        for (int col = 0; col < (*it)->columnCount(); ++col) {
            (*it)->setBackground(col, QBrush(Qt::white));
            (*it)->setForeground(col, QBrush(Qt::black));
        }
        ++it;
    }
    treeWidget->setCurrentItem(nullptr);
}

QTreeWidgetItem* myFileManager::findAndHighlight(QTreeWidgetItem *item, const QString &keyword, bool firstMatchFound)
{
    if(keyword=="")return nullptr;
    if (!item) return nullptr;

    QTreeWidgetItem *firstMatchInBranch = nullptr;
    bool currentItemMatched = false;

    // 检查当前项的所有列
    for (int col = 0; col < item->columnCount(); ++col) {
        if (item->text(col).contains(keyword, Qt::CaseInsensitive)) {
            // 高亮匹配项
            item->setBackground(col, QBrush(QColor(255, 255, 0))); // 黄色背景
            item->setForeground(col, QBrush(Qt::black));
        }
    }

    // 递归检查子项
    for (int i = 0; i < item->childCount(); ++i) {
        QTreeWidgetItem *childMatch = findAndHighlight(item->child(i), keyword, firstMatchFound);
        if (childMatch && !firstMatchInBranch) {
            firstMatchInBranch = childMatch;
            item->setExpanded(true); // 展开父项以便显示匹配的子项
        }
    }

    return firstMatchInBranch;
}

QString myFileManager::getItemPath(QTreeWidgetItem* item) {
    QStringList pathParts;
    while (item) {
        pathParts.prepend(item->text(0));
        item = item->parent();
    }
    QString a=pathParts.join("/");
    return a;

}

bool myFileManager::renameFile(const QString &oldPath, const QString &newName)
{
    QFileInfo oldInfo(oldPath);
    if (!oldInfo.exists()) {
        qDebug() << "文件不存在:" << oldPath;
        return false;
    }
    QString newPath = oldInfo.dir().filePath(newName);
    // 避免重复名称
    if (QFileInfo::exists(newPath)) {
        qDebug() << "目标文件已存在:" << newPath;
        return false;
    }
    QFile file(oldPath);
    if (!file.rename(newPath)) {
        qDebug() << "重命名失败:" << file.errorString();
        return false;
    }

    return true;
}

QJsonObject myFileManager::loadConfig(const QString &path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());    
    return doc.object();
}

// HTML适配函数（解决Qt渲染差异）
QString myFileManager::adaptHtmlForQt(const QString &originalHtml)
{
    QString adapted = originalHtml;
    adapted.replace("px", "pt");
    adapted.insert(6, "<style>body { font-family: 'Arial'; }</style>");
    adapted.replace("<table", "<table border='1' cellpadding='2'");
    return adapted;
}
//使用案例QJsonObject config = loadConfig(":/config.json");
//QString encryptedToken = config["encrypted_token"].toString();
