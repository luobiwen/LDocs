#ifndef MYDSMANAGER_H
#define MYDSMANAGER_H
#include"QString"
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include<qconfig.h>
class myDSManager: public QObject{
public:
    myDSManager(QObject *parent = nullptr): QObject(parent){}
    void sendRequest(const QString &prompt);

private:
    QNetworkReply *reply;
    QJsonObject requestBody;
    QNetworkAccessManager *manager;
};
#endif // MYDSMANAGER_H
