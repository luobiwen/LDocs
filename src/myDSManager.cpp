#include"myDSManager.h"
#include"myFileManager.h"

void myDSManager::sendRequest(const QString &prompt){//有回答了 不过我网络有点不好 改天再试试
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // 1. 构造请求 JSON
    QJsonObject requestBody;
    requestBody["model"] = "deepseek-chat";
    requestBody["temperature"] = 0.7;

    QJsonArray messages;
    QJsonObject message;
    message["role"] = "user";
    message["content"] = prompt;
    messages.append(message);
    requestBody["messages"] = messages;

    QJsonDocument doc(requestBody);
    QByteArray data = doc.toJson();

    // 2. 配置请求头
    QNetworkRequest request;
    QJsonObject jsonobject=myFileManager().loadConfig(":/config/config.json");
    request.setUrl(QUrl(jsonobject["apiUrl"].toString()));
    QString token=jsonobject["apiKey"].toString();
    request.setRawHeader("Authorization",QByteArray("Bearer "+token.toUtf8()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 3. 发送 POST 请求
    QNetworkReply *reply = manager->post(request, data);
    // 4. 处理响应
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument responseDoc = QJsonDocument::fromJson(response);
            QJsonObject root = responseDoc.object();

            if (root.contains("choices") && root["choices"].isArray()) {
                QJsonArray choices = root["choices"].toArray();
                if (!choices.isEmpty()) {
                    QJsonObject choice = choices[0].toObject();
                    QJsonObject message = choice["message"].toObject();
                    qDebug() << "回答:" << message["content"].toString();
                }
            }
        } else {
            qDebug() << "请求失败:" << reply->errorString();
        }

        // 清理资源
        reply->deleteLater();
        manager->deleteLater();
    });
}



