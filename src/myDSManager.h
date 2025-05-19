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
    Q_OBJECT
public:
    myDSManager(QObject *parent = nullptr);
    void sendRequest(const QString &prompt);

signals:
    void responseReceived(const QString &text); // 传递API响应的信号
private:
    QJsonObject requestBody;
    QNetworkAccessManager *manager;
};
#endif // MYDSMANAGER_H
