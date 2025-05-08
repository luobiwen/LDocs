#include"myFileManager.h"

QFileInfoList myFileManager::FiletoList(QString dicpath,QTreeWidgetItem* rootitem){
    QDir dir(dicpath);
    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    foreach (QFileInfo var, file_list) {
        if(var.isDir()){
            QTreeWidgetItem* child=new QTreeWidgetItem(QStringList()<<var.fileName());
            rootitem->addChild(child);
            qDebug()<<var.fileName();
            QFileInfoList child_file_list = FiletoList(var.absoluteFilePath(),child);
            file_list.append(child_file_list);
            file_list.append(var);
        }
        else if(var.isFile()){
            QTreeWidgetItem *childitem=new QTreeWidgetItem(QStringList() <<var.fileName());
            rootitem->addChild(childitem);
            qDebug()<<var.fileName();
        }
    }
    return file_list;
}

void myFileManager::NewFile(QString filepath,QString filename){
    QString fullpath = filepath + "/" + filename;
    QFile file(fullpath);
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

void myFileManager::EditFileName(QString filepath,QLineEdit* lineedit){
    QString newfilename = lineedit->text();
    QFile file(filepath);
    QFileInfo fileinfo(file);
    QString filedirpath=fileinfo.absolutePath();
    file.rename(filedirpath+"/"+newfilename);
}

QJsonObject myFileManager::loadConfig(const QString &path) {
    QFile file(path);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return doc.object();
}
//使用案例QJsonObject config = loadConfig(":/config.json");
//QString encryptedToken = config["encrypted_token"].toString();
