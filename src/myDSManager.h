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
    const QString apiUrl = "https://api.deepseek.com/v1/chat/completions";
    const QString apiKey = "sk-184cd9c0dba04ab78723743e89c01cb6";
    QJsonObject requestBody;
    QNetworkAccessManager *manager;
};
#endif // MYDSMANAGER_H
