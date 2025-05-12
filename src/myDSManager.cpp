#include"myDSManager.h"
void myDSManager::handleResponse(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return;
    
    }
    // 解析响应
    QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonResponse = response.object();
    if (jsonResponse.contains("choices")) {
        QJsonArray choices = jsonResponse["choices"].toArray();
    if (!choices.isEmpty()) {
        QJsonObject choice = choices.first().toObject();
        QJsonObject message = choice["message"].toObject();
        QString content = message["content"].toString();
        qDebug() << "API Response:" << content;
        }
    } else {
        qDebug() << "Error response:" << response.toJson();
    }
    reply->deleteLater();
    return;
}

void myDSManager::sendRequest(const QString &prompt){
    // API配置
    QJsonObject config = myFileManager().loadConfig(":/config.json");
    QString encryptedToken = config["encrypted_token"].toString();
    const QString apiUrl = "https://api.deepseek.com/v1/chat/completions";
    const QString apiKey = encryptedToken;
    // 创建请求
    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());
    // 构建JSON请求体
    QJsonObject requestBody;
    requestBody["model"] = "deepseek-chat"; // 根据实际模型名称修改
    requestBody["temperature"] = 0.7;
    requestBody["max_tokens"] = 1000;
    QJsonArray messages;
    QJsonObject systemMsg;
    systemMsg["role"] = "system";
    systemMsg["content"] = "You are a helpful assistant.";
    messages.append(systemMsg);
    QJsonObject userMsg;
    userMsg["role"] = "user";
    userMsg["content"] = prompt;
    messages.append(userMsg);
    requestBody["messages"] = messages;
    // 发送POST请求
    manager->post(request, QJsonDocument(requestBody).toJson());
}

