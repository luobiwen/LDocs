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
#include"myFileManager.h"
class myDSManager: public QObject{
public:
    explicit myDSManager(QObject *parent = nullptr) : QObject(parent) {
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished,
                this, &myDSManager::handleResponse);
    }
    void sendRequest(const QString &prompt);
private slots:
    void handleResponse(QNetworkReply *reply);
private:
    QJsonObject requestBody;
    QNetworkAccessManager *manager;
};
#endif // MYDSMANAGER_H
